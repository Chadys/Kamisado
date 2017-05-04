"""Interfacer"""
# pylint: disable=line-too-long
import sys
from subprocess import Popen, PIPE, STDOUT
from nbstreamreader import NonBlockingStreamReader as NBSR
import time

PROG_AI1 = 0
PROG_AI2 = 1
PROG_REF = 2
PROG_DIS = 3

TIMEOUT_AI = 10
TIMEOUT_HUMAN = None
TIMEOUT_DISPLAYER = 3
TIMEOUT_REF = 5


GREEN = "\033[0;32m"
BLUE  = "\033[0;34m"
RED   = "\033[1;31m"
RESET = "\033[0;0m"

HUMAN = 1
COMP = 0

PROCESSES = []

def end(ia_):
    """"Send close command to all processes and print winner"""
    if ia_ != -1:
        print(RED+"{} won !".format(PROCESSES[ia_]['name'])+RESET)
        if len(PROCESSES) == 4:
            if communicate(PROCESSES[PROG_DIS], 'endgame ' + str(ia_) + '\n', 2.0, except_none=True) != "OK":
                print_fail(PROG_DIS, "endgame")
            time.sleep(25)
    print("Exiting... ({})".format(ia_))
    for i, process in enumerate(PROCESSES):
        if process['type'] == COMP:
            if communicate(process, 'quit\n', 0.5, except_none=True) != "OK":
                print_fail(i, "quit")
            process['process'].kill()
    exit()


def eval_bool(bool1, bool2):
    """Return 2 if both bool are true, -1 if they are both false
    the identifier of the true one otherwise"""
    count = 2
    if not bool1:
        count-=1
    if not bool2:
        count-=2
    return count

def init_processes(length):
    """Send init command to all processes"""
    for i in range(1, length):
        print('{} : {}'.format(i - 1, sys.argv[i]))
        if sys.argv[i] == "human" and i < 3:
            if length == 5:
                PROCESSES.append({'type':HUMAN, 'id':i - 1})
            else:
                print(RED+"To play as a human, you need a displayer executable\n"+RESET)
                end(-1)
        else:
            process = Popen(sys.argv[i], bufsize=0,
                            stdin=PIPE,
                            stdout=PIPE,
                            stderr=sys.stdout)
            nbsr = NBSR(process.stdout, doprint=False, idd=i - 1)
            PROCESSES.append({'type':COMP, 'process':process, 'nbsr':nbsr, 'id':i - 1})

    PROCESSES[PROG_AI1]['name'] = "AI1"
    PROCESSES[PROG_AI2]['name'] = "AI2"
    PROCESSES[PROG_REF]['name'] = "REFEREE"
    if length == 5:
        PROCESSES[PROG_DIS]['name'] = "DISPLAYER"
    if not communicate(PROCESSES[PROG_REF], 'init\n', 2, except_none=True) == "OK":
        print_fail(PROG_REF, "init")


    if PROCESSES[PROG_AI1]['type'] == HUMAN:
        val1 = 1
    else:
        val1 = communicate(PROCESSES[PROG_AI1], 'init\n', 2, except_none=True) == "OK"

    if PROCESSES[PROG_AI2]['type'] == HUMAN:
        val2 = 1
    else:
        val2 = communicate(PROCESSES[PROG_AI2], 'init\n', 2, except_none=True) == "OK"

    for i, val in enumerate([val1, val2]):
        if not val:
            print_fail(i, "init")
    check = eval_bool(val1, val2)
    if check < 2:
        end(check)

    first_human = False;
    if PROCESSES[PROG_AI1]['type'] == HUMAN:
        name1 = "Human"
        first_human = True
    else:
        name1 = communicate(PROCESSES[PROG_AI1], 'name\n', 2)

    if PROCESSES[PROG_AI2]['type'] == HUMAN:
        name2 = "Human 2" if first_human else "Human"
    else:
        name2 = communicate(PROCESSES[PROG_AI2], 'name\n', 2)

    val1 = name1 is not None
    val2 = name2 is not None
    for i, val in enumerate([val1, val2]):
        if not val:
            print_fail(i, "name")
    check = eval_bool(val1, val2)
    if check < 2:
        end(check)
    PROCESSES[PROG_AI1]['name'] = name1
    PROCESSES[PROG_AI2]['name'] = name2

    if length == 5:
        if not communicate(PROCESSES[PROG_DIS], 'init\n', 2, except_none=True) == "OK":
            print_fail(PROG_DIS, "init")
        if communicate(PROCESSES[PROG_DIS], 'names {};{}\n'.format(name1, name2), 2.0, except_none=True) != "OK":
            print_fail(PROG_DIS, "names")

def communicate(program_, command_, timeout_, except_none=False):
    """Send command to a program and return its answer"""
    stream = program_['process'].stdin
    stream.write(command_.encode())
    stream.flush()
    res = program_['nbsr'].readline(timeout_)
    if res:
        res = res.split()
        if res:
            if res[0] == "=":
                del res[0]
                if not res and except_none:
                    return 'OK'
                if res and res[0] != "?":
                    return ' '.join(res)
    return None


def get_ref(command_, timeout_):
    """Get the referee's answer for an AI's move"""
    res = communicate(PROCESSES[PROG_REF], command_, timeout_)
    if res:
        res = int(''.join(res))
    else:
        return None
    if res >= 0 and res <= 2:
        return res
    return None

def ask_ia_or_human(_ia):
    """Send genmove to correct process depending on the type of it"""
    if PROCESSES[_ia]['type'] == COMP:
        res = communicate(PROCESSES[_ia], 'genmove\n', TIMEOUT_AI)
    else:
        print("ASKING TO HUMAN")
        res = communicate(PROCESSES[PROG_DIS], 'genmove\n', TIMEOUT_HUMAN)
    return res

def notify_ia(_ia, _command):
    """Send move to process"""
    if PROCESSES[_ia]['type'] == COMP:
        return communicate(PROCESSES[_ia], _command, TIMEOUT_REF, except_none=True) is "OK"
    else:
        return True

def main_loop(use_display, c_ia):
    """Main loop of the program"""
    if use_display:
        print('I use display')
    else:
        print('No graphic display')
    c_adv = int(not c_ia)
    while True:
        time.sleep(0.5)
        print(GREEN+'\nPlayer : {}'.format(c_ia)+RESET)
        print(BLUE+'Sending [genmove] to {}'.format(PROCESSES[c_ia]['name'])+RESET)
        res_ia = ask_ia_or_human(c_ia)
        if not res_ia:
            print_fail(c_ia, "genmove")
            end(c_adv)

        print('{} anwser [{}]'.format(PROCESSES[c_ia]['name'], res_ia))
        print('Sending [move {}] to REFEREE'.format(res_ia))
        res_ref = get_ref('move {}\n'.format(res_ia), 8.0)
        print('REFEREE answer [{}]'.format(res_ref))
        if res_ref is None or res_ref < 0 or res_ref > 2:
            print_fail(PROG_REF, "move")
            end(-1)
        if res_ref == 0:
            print_fail(c_ia, "genmove")
            print("REFEREE decided it was illegal.\n")
            end(c_adv)
        elif res_ref == 2:
            if use_display:
                print('Sending [move {}] to DISPLAYER'.format(res_ia))
                if communicate(PROCESSES[PROG_DIS], 'move ' + res_ia + '\n', 0.5, except_none=True) != "OK":
                    print_fail(PROG_DIS, "move")
            end(c_ia)

        print(BLUE+'Sending [move {}] to {}'.format(res_ia, PROCESSES[c_adv]['name'])+RESET)
        if not notify_ia(c_adv, 'move {}\n'.format(res_ia)):
            print_fail(c_adv, "move")
            end(c_ia)
        else:
            print("{} OK".format(PROCESSES[c_adv]['name']))

        if use_display:
            print('Sending [move {}] to DISPLAYER'.format(res_ia))
            if communicate(PROCESSES[PROG_DIS], 'move ' + res_ia + '\n', 0.5, except_none=True) != "OK":
                print_fail(PROG_DIS, "move")

        c_ia = c_adv
        c_adv = int(not c_ia)

def print_fail(index_prog, name_command):
    """Display text if a process answered incorrectly to a command"""
    print('{} failed for [{}] command.\n'.format(PROCESSES[index_prog]['name'], name_command))


if __name__ == "__main__":
    print(sys.argv)
    length = len(sys.argv)
    if length < 4 or length > 5:
        print('Arguments : AI1, AI2, Referee, Display (facultative)')
        exit()
    init_processes(length)
    print(RED+'Init finished'+RESET)
    main_loop(bool(length - 4), 0)
