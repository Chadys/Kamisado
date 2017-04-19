"""Interfaçeur"""
# pylint: disable=line-too-long
import sys
from subprocess import Popen, PIPE, STDOUT
from nbstreamreader import NonBlockingStreamReader as NBSR
import time

PROG_IA1 = 0
PROG_IA2 = 1
PROG_ARB = 2
PROG_DIS = 3

GREEN = "\033[0;32m"
RESET = "\033[0;0m"


PROCESSES = []

def end(ia_):
    """"Senc close command to all process and print winner"""
    if ia_ != -1:
        if communicate(PROCESSES[PROG_DIS], 'endgame ' + str(ia_) + '\n', 2.0, except_none=True) != "OK":
            print('DISPLAYER failed for [endgame] command.')
        time.sleep(5)

    print("Exiting... ({})".format(ia_))
    for i, process in enumerate(PROCESSES):
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
        process = Popen(sys.argv[i], bufsize=0,
                        stdin=PIPE,
                        stdout=PIPE,
                        #stdout=io.FileIO('out{}.txt'.format(i - 1), 'w'),
                        stderr=STDOUT)
        nbsr = NBSR(process.stdout, doprint=False, idd=i - 1)
        #NBSR(process.stdin, doprint=True, idd=i+9)
        PROCESSES.append({'process':process, 'nbsr':nbsr, 'id':i - 1})

    if not communicate(PROCESSES[PROG_ARB], 'init\n', 2, except_none=True) == "OK":
        print('ARBITRATOR failed for [init] command.')

    val1 = communicate(PROCESSES[PROG_IA1], 'init\n', 2, except_none=True) == "OK"
    val2 = communicate(PROCESSES[PROG_IA2], 'init\n', 2, except_none=True) == "OK"
    for i, val in enumerate([val1, val2]):
        if not val:
            print('PROG_{} failed for [init] command.'.format(i))
    check = complicated(val1, val2)
    if check < 2:
        end(check)

    name1 = communicate(PROCESSES[PROG_IA1], 'name\n', 2)
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
    PROCESSES[PROG_IA2]['name'] = name2 + "test"

    if length == 5 :
        if communicate(PROCESSES[PROG_DIS], 'names {};{}\n'.format(name1, name2), 2.0, except_none=True) != "OK":
            print('DISPLAYER failed for [names] command.')
            end(-1)

def communicate(program_, command_, timeout_, except_none=False):
    """Send command to a program and return his answer"""
    #print(color + 'TO [{}] : [{}]'.format(program_['id'], command_.strip())+ RESET)
    stream = program_['process'].stdin
    stream.write(command_.encode())
    stream.flush()
    #print(color+'### stream id : {}'.format(stream)+RESET)
    res = program_['nbsr'].readline(timeout_)
    # if res:
    #     print(color+'FROM [{}] : [{}]'.format(program_['id'], ' '.join(res.split()))+RESET)
    # else:
    #     print(color + 'no res' + RESET)
    #print('receive [{}]'.format(res.strip()))
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


def get_arb(command_, timeout_):
    """Get the arbitrator's answer for an IA move"""
    res = communicate(PROCESSES[PROG_ARB], command_, timeout_)
    #print('REPONSE ARBITRE -get arb: [{}]'.format(res))
    if res:
        res = int(''.join(res))
    else:
        return None
    if res >= 0 and res <= 2:
        #print('in')
        return res
    return None

def main_loop(use_display, c_ia):
    """Boucle principale du programme"""
    if use_display:
        print('i use display')
    else:
        print('nope')
    c_adv = int(not c_ia)
    while True:
        time.sleep(0.5)
        print(GREEN+'\nPlayer : {}'.format(c_ia)+RESET)
        print('\033[1;34msending [genmove] to IA{}'.format(c_ia)+RESET)
        res_ia = communicate(PROCESSES[c_ia], 'genmove\n', 10.0)
        if not res_ia:
            print("IA{} failed for [genmove] command\n".format(c_ia))
            end(c_adv)
        print('IA{} anwser [{}]'.format(c_ia, res_ia))
        print('sending [move {}] to arbitrator'.format(res_ia))
        res_arb = get_arb('move {}\n'.format(res_ia), 8.0)
        print('ARBITRATOR answer [{}]'.format(res_arb))
        if not res_arb or res_arb < 0 or res_arb > 2:
            end(-1)
        if res_arb == 0:
            end(c_adv)
        elif res_arb == 2:
            end(c_ia)

        print('\033[1;34mSending [move {}] to IA{}'.format(res_ia, c_adv)+RESET)
        if communicate(PROCESSES[c_adv], 'move {}\n'.format(res_ia), 2, except_none=True) != "OK":
            print("IA{} failed for [move] command\n".format(c_adv))
            end(c_ia)
        else:
            print("IA{} OK".format(c_adv))

        if use_display:
            print('sending [move {}] to DISPLAYER'.format(res_ia))
            if communicate(PROCESSES[PROG_DIS], 'move ' + res_ia + '\n', 0.5, except_none=True) != "OK":
                print('DISPLAYER failed for [move] command\n')
                end(-1)

        c_ia = c_adv
        c_adv = int(not c_ia)
   


if __name__ == "__main__":
    print(sys.argv)
    length = len(sys.argv)
    if length < 4 or length > 5:
        print('Arguments : IA1, IA2, Arbitrator, Display (facultative)')
        exit()
    init_processes(length)
    print('\033[1;31mfinished'+RESET)
    main_loop(bool(length - 4), 0)
