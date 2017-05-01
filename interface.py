"""Interfaçeur"""
# pylint: disable=line-too-long
import sys
from subprocess import Popen, PIPE, STDOUT
from nbstreamreader import NonBlockingStreamReader as NBSR
import time

PROG_IA1 = 0
PROG_IA2 = 1
PROG_REF = 2
PROG_DIS = 3

TIMEOUT_IA = 10
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
    """"Send close command to all process and print winner"""
    if ia_ != -1:
        print(RED+"{} won !".format(PROCESSES[ia_]['name'])+RESET)
        if len(PROCESSES) == 4:
            if communicate(PROCESSES[PROG_DIS], 'endgame ' + str(ia_) + '\n', 2.0, except_none=True) != "OK":
                print('DISPLAYER failed for [endgame] command.')
            time.sleep(24)
    print("Exiting... ({})".format(ia_))
    for i, process in enumerate(PROCESSES):
        if process['type'] == COMP:
            if communicate(process, 'quit\n', 0.5, except_none=True) != "OK":
                print('PROG_{} failed for [quit] command.\n'.format(i))
            process['process'].kill()
    exit()


def complicated(bool1, bool2):
    """Do a complicated thing"""
    if not (bool1 and bool2):
        if not(bool1 or bool2):
            return -1
        return int(bool1 is not True)
    return 2

def init_processes(length):
    """Send init command to all processes"""
    for i in range(1, length):
        print('{} : {}'.format(i - 1, sys.argv[i]))
        if sys.argv[i] == "human":
            PROCESSES.append({'type':HUMAN, 'id':i - 1})
        else:
            process = Popen(sys.argv[i], bufsize=0,
                            stdin=PIPE,
                            stdout=PIPE,
                            #stdout=io.FileIO('out{}.txt'.format(i - 1), 'w'),
                            stderr=STDOUT)
            nbsr = NBSR(process.stdout, doprint=False, idd=i - 1)
            #NBSR(process.stdin, doprint=True, idd=i+9)
            PROCESSES.append({'type':COMP, 'process':process, 'nbsr':nbsr, 'id':i - 1})

    if not communicate(PROCESSES[PROG_REF], 'init\n', 2, except_none=True) == "OK":
        print('REFEREE failed for [init] command.')


    if PROCESSES[PROG_IA1]['type'] == HUMAN:
        val1 = 1
    else:
        val1 = communicate(PROCESSES[PROG_IA1], 'init\n', 2, except_none=True) == "OK"

    if PROCESSES[PROG_IA2]['type'] == HUMAN:
        val2 = 1
    else:
        val2 = communicate(PROCESSES[PROG_IA2], 'init\n', 2, except_none=True) == "OK"

    for i, val in enumerate([val1, val2]):
        if not val:
            print('PROG_{} failed for [init] command.'.format(i))
    check = complicated(val1, val2)
    if check < 2:
        end(check)


    if PROCESSES[PROG_IA1]['type'] == HUMAN:
        name1 = "Human 1"
    else:
        name1 = communicate(PROCESSES[PROG_IA1], 'name\n', 2)

    if PROCESSES[PROG_IA2]['type'] == HUMAN:
        name2 = "Human 2"
    else:
        name2 = communicate(PROCESSES[PROG_IA2], 'name\n', 2)

    val1 = name1 is not None
    val2 = name2 is not None
    for i, val in enumerate([val1, val2]):
        if not val:
            print('PROG_{} failed for [name] command.'.format(i))
    check = complicated(val1, val2)
    if check < 2:
        end(check)
    PROCESSES[PROG_IA1]['name'] = name1
    PROCESSES[PROG_IA2]['name'] = name2

    if length == 5:
        if not communicate(PROCESSES[PROG_DIS], 'init\n', 2, except_none=True) == "OK":
            print('DISPLAYER failed for [init] command.')
        if communicate(PROCESSES[PROG_DIS], 'names {};{}\n'.format(name1, name2), 2.0, except_none=True) != "OK":
            print('DISPLAYER failed for [names] command.')

def communicate(program_, command_, timeout_, except_none=False):
    """Send command to a program and return his answer"""
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
    """Get the referee's answer for an IA move"""
    res = communicate(PROCESSES[PROG_REF], command_, timeout_)
    if res:
        res = int(''.join(res))
    else:
        return None
    if res >= 0 and res <= 2:
        return res
    return None

def ask_ia_or_human(_ia):
    """Ask for genmove to process"""
    if PROCESSES[_ia]['type'] == COMP:
        res = communicate(PROCESSES[_ia], 'genmove\n', TIMEOUT_IA)
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
    """Boucle principale du programme"""
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
            print("{} failed for [genmove] command\n".format(PROCESSES[c_ia]['name']))
            end(c_adv)

        print('{} anwser [{}]'.format(PROCESSES[c_ia]['name'], res_ia))
        print('Sending [move {}] to referee'.format(res_ia))
        res_ref = get_ref('move {}\n'.format(res_ia), 8.0)
        print('REFEREE answer [{}]'.format(res_ref))
        if res_ref is None or res_ref < 0 or res_ref > 2:
            print('REFEREE failed for [move] command.')
            end(-1)
        if res_ref == 0:
            print("{} failed for [genmove] command (illegal move)\n".format(PROCESSES[c_ia]['name']))
            end(c_adv)
        elif res_ref == 2:
            if use_display:
                print('Sending [move {}] to DISPLAYER'.format(res_ia))
                if communicate(PROCESSES[PROG_DIS], 'move ' + res_ia + '\n', 0.5, except_none=True) != "OK":
                    print('DISPLAYER failed for [move] command\n')
            end(c_ia)

        print(BLUE+'Sending [move {}] to {}'.format(res_ia, PROCESSES[c_adv]['name'])+RESET)
        if not notify_ia(c_adv, 'move {}\n'.format(res_ia)):
            print("{} failed for [move] command\n".format(PROCESSES[c_adv]['name']))
            end(c_ia)
        else:
            print("{} OK".format(PROCESSES[c_adv]['name']))

        if use_display:
            print('Sending [move {}] to DISPLAYER'.format(res_ia))
            if communicate(PROCESSES[PROG_DIS], 'move ' + res_ia + '\n', 0.5, except_none=True) != "OK":
                print('DISPLAYER failed for [move] command\n')

        c_ia = c_adv
        c_adv = int(not c_ia)



if __name__ == "__main__":
    print(sys.argv)
    length = len(sys.argv)
    if length < 4 or length > 5:
        print('Arguments : AI1, AI2, Referee, Display (facultative)')
        exit()
    init_processes(length)
    print(RED+'Init finished'+RESET)
    main_loop(bool(length - 4), 0)
