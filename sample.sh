#!/bin/sh

set -e
set -u
set -C

# global variables
SCRIPT_NAME="$(basename $0)"
SCRIPT_PATH="$(dirname $0)"

# option arguments
VERBOSE=0
INFILE=""
OUTFILE=""

verbose ()
{
    [ $VERBOSE -ne 0 ] && >&2 echo "$@" || true
}

error ()
{
    >&2 echo "$@"
}

# print basic usage information for the program
show_help ()
{
	error "Usage:
  ${SCRIPT_NAME} [options]

This script will read input from stdin, perform some computation, and write the
resulting output to stdout.

Options:
  -h, --help           show this help message and exit
  -i, --input INPUT    specify an input file
  -o, --output OUTPUT  specify an output file
  -v, --verbose        extra output for debug
"
}

# parse command line input options and return status
parse_args ()
{
    local options
    options=$(getopt -o "hi:o:v" \
		-l "help,input:,output:,verbose" \
		-n "${SCRIPT_NAME}" \
		-- "$@") || {
		show_help
		return 1
	}

	eval set -- "$options"
	while [ $# -gt 0 ]; do
	    verbose $1
		case "$1" in
			-h|--help)
				show_help
				return 0
			;;

			-v|--verbose)
				VERBOSE=1
				verbose $1
			;;

			-i|--input)
				shift
				INFILE="$1"
			;;

			-o|--output)
				shift
				OUTFILE="$1"
			;;

			--)
				shift
				break
			;;
		esac
		shift
	done

    return 0
}

# main logic
script_main ()
{
    local input
    local numlines

    parse_args "$@" || return $?

    # read from input
    # ...
    [ -z "${INFILE}" ] && {
        input="$(cat --)"
    } || {
        input="$(cat "${INFILE}")"
    }

    # perform calculation
    # ...
    numlines=$(echo "${input}" |wc -l)
    verbose ${numlines} lines read

    # write output
    # ...
    [ -z "${OUTFILE}" ] && {
        echo "${input}"
    } || {
        echo "${input}" >${OUTFILE}
    }

}

script_main "$@"

