#!/usr/bin/env python
import argparse
import os
from sys import exit
import subprocess
from time import sleep

# COLORS
WARNING = '\033[93m'
FAIL = '\033[91m'
ENDC = '\033[0m'
BOLD = '\033[1m'

def parse_args():
    '''
        parse arguments from command line
        --number : number of times to loop
        --interval : time to sleep between iterations
        --command : command to run
        returns a namespace of arguments
    '''
    parser = argparse.ArgumentParser(description='Refresh runs arbitrary commands at arbitrary intervals.', prog='re')
    parser.add_argument('--number', '-n', help='Number of times to loop. Defaults to infinite.', default=-1, type=int)
    parser.add_argument('--interval', '-i', help='Number of seconds to wait between loops. Defaults to 1 second.', default=1, type=float)
    parser.add_argument('--nowipe', '-w', help='''Don't wipe the screen after every loop''', action='store_true', default=False)
    parser.add_argument('--timeout', '-t', help='Timeout (seconds) to wait for the process to finish. Defaults to none.', default=None)
    parser.add_argument('--debug', '-d', help='Enables debug mode.', action='store_true', default=False)
    parser.add_argument('--command', '-c', help='The command to loop. Pipes and special characters must be quoted!', nargs=argparse.REMAINDER)
    return parser.parse_args()

def main():
    try:
        loops = 0
        args = parse_args()
        if args.debug:
            print '{}DEBUG {}ENV{} {}'.format(WARNING, BOLD, ENDC, os.environ)
            print '{}DEBUG {}CMD{} {}'.format(WARNING, BOLD, ENDC, args.command)
            print '{}DEBUG {}NUM{} {}'.format(WARNING, BOLD, ENDC, args.number)
            print '{}DEBUG {}INT{} {}'.format(WARNING, BOLD, ENDC, args.interval)
            print '{}DEBUG {}CLR{} {}'.format(WARNING, BOLD, ENDC, args.nowipe)
            print '{}DEBUG {}TIM{} {}'.format(WARNING, BOLD, ENDC, args.timeout)
            print BOLD + ''.join(['-' for char in range(28)]), ENDC
            exit(0)
        while True:
            if args.number == loops:
                break
            loops += 1
            if not args.nowipe:
                os.system('cls' if os.name == 'nt' else 'clear')
            ux = '''{}COMMAND:{} {:>16} | {}INTERVAL:{} {:>3} | {}LOOPS:{} {}/{}{}'''.format(
                BOLD, ENDC, ' '.join(args.command), BOLD, ENDC, args.interval, BOLD, ENDC, loops, args.number,ENDC)
            print ux
            print BOLD + ''.join(['-' for char in range(len(ux) - 28)]), ENDC
            p = subprocess.Popen(args.command, env=os.environ, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            out, err =  p.communicate()
            print out
            print FAIL + err + ENDC
            if args.timeout:
                sleep(args.timeout)
                p.kill()
            sleep(args.interval)
    except KeyboardInterrupt as e:
        print ''
        print WARNING + 'Caught CTRL+C; exiting' + ENDC
        p.kill()
    except Exception as e:
        print e
        p.kill()
    finally:
        exit(0)

if __name__ == '__main__':
    main()


#EOF

# (C) 2017 PETER CHRISTIAN FRAEDRICH
# MIT LICENSE (see license in local folder)