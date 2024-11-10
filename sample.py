#!/bin/python
import argparse
import sys

#globals
args=argparse.Namespace()

def verbose(*objects, sep=' ', end='\n', flush=False):
    """verbose log output"""
    global args
    if (args.verbose):
        print(*objects, sep=sep, end=end, flush=flush, file=sys.stderr)

def error(*objects, sep=' ', end='\n', flush=False):
    """error log output"""
    print(*objects, sep=sep, end=end, flush=flush, file=sys.stderr)

def parse_args(inargs) -> argparse.Namespace:
    """parse command line input options and return the argparse namespace"""

    parser = argparse.ArgumentParser(description=
        """This script will read input from stdin, perform some computation, and write the resulting output to stdout."""
    )
    parser.add_argument("-i", "--input", default=sys.stdin,
        type=argparse.FileType('r', encoding="ascii"),
        help="specify an input file")
    parser.add_argument("-o", "--output", default=sys.stdout,
        type=argparse.FileType('w'), help="specify an output file")
    parser.add_argument("-v", "--verbose", action="store_true",
        help="extra output for debug")
    return(parser.parse_args(inargs))

def script_main(inargs) -> int:
    """main logic"""
    global args

    args=parse_args(inargs)
    verbose(args)

    # read from input
    # ...
    lines=[]
    for line in args.input:
        lines.append(line)
    verbose("read {} lines".format(len(lines)))

    # perform calculation
    # ...
    if (0 == len(lines)):
        error("Error: no input available")

    # write output
    # ...
    for line in lines:
        print(line, end='')

if __name__ == "__main__":
    sys.exit(script_main(sys.argv[1:]))
