#include <getopt.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>

/*===========================    #define values    ===========================*/

/*===========================   global variables   ===========================*/
/* option arguments */
bool option_verbose = false;
const char* option_input_file = NULL;
const char* option_output_file = NULL;

/*=========================== function  prototypes ===========================*/

/*=========================== function-like macros ===========================*/
/* verbose logging */
#define verbose(...) \
    do { \
        if (option_verbose) fprintf(stderr, __VA_ARGS__); \
    } while(0)

/* error logging */
#define error(...) \
    do { \
        fprintf(stderr, __VA_ARGS__); \
    } while(0)

/*=========================== function definitions ===========================*/
/* print basic usage information for the program
   note: calls exit(exit_code) at end and does not return */
noreturn void print_help(const char* const pname, int exit_code)
{
    fprintf(stderr, "\
Usage:\n\
  %s [-v] [-h] [-i INPUT] [-o OUTPUT]\n\
\n\
This program will read input from stdin, perform some computation, and write\n\
the resulting output to stdout.\n\
\n\
options:\n\
  -v, --verbose               extra output for debug\n\
  -h, --help                  show this help message and exit\n\
  -i INPUT, --input INPUT     specify an input file (default stdin)\n\
  -o OUTPUT, --output OUTPUT  specify an output file (default stdout)\n\
", pname);

    exit(exit_code);
}

/* parse command line input options and return status */
int parse_args(int argc, char* const argv[])
{
    int retval = 0;
    static const char* optstring = "i:o:hv";
    static struct option long_options[] = {
        {"input",   required_argument, 0, 'i'},
        {"output",  required_argument, 0, 'o'},
        {"help",    no_argument,       0, 'h'},
        {"verbose", no_argument,       0, 'v'},
        {0,         0,                 0, 0}
    };
    int c = 0;
    const char* const pname = argv[0];

    /* loop until c == -1 indicating end of options help message was printed */
    while (-1 != c) {
        c = getopt_long(argc, argv, optstring, long_options, NULL);
        if (c > 0)
            verbose("read option %c, with optarg %s\n", c, optarg);

        switch(c) {
            case -1:
                /* no action, end of arguments */
/*END*/         break;

            case 'v':
                option_verbose = true;
                break;

            case 'h':
/*BREAK*/       c=-1;
/*NORETURN*/    print_help(pname, 0);
                break;

            case 'i':
                option_input_file = optarg;
                break;

            case 'o':
                option_output_file = optarg;
                break;

            case '?':
                /* intentional fall-through */
            default:
                retval=1;
/*BREAK*/       c=-1;
/*NORETURN*/    print_help(pname, 1);
                break;
        }
    }

    return retval;
}

/* main logic */
int main(int argc, char* const argv[])
{
    int retval = 0;

    // parse arguments
    retval = parse_args(argc, argv);

    // redirect input and output
    if ((0 == retval) && (NULL != option_input_file)) {
        if (NULL == freopen(option_input_file, "r", stdin)) {
          error("Failed to open input file %s\n", option_input_file);
          retval = -1;
        }
    }

    if ((0 == retval) && (NULL != option_output_file)) {
        if (NULL == freopen(option_output_file, "w", stdout)) {
            error("Failed to open output file %s\n", option_output_file);
            retval = -1;
        }
    }

    if (0 == retval) {
        // read from input
        // ...
        char buffer[81];
        size_t sizeresult;
        sizeresult = fread(buffer, 1, 79, stdin);

        // perform calculation
        // ...
        if (sizeresult <= 0) {
            buffer[0] = '\n';
            buffer[1] = 0;
            sizeresult=1;
            error("no input provided\n");
        } else if (sizeresult < 80) {
            if ('\n' == buffer[sizeresult-1]) {
                buffer[sizeresult] = 0;
            } else {
                buffer[sizeresult] = '\n';
                buffer[sizeresult+1] = 0;
                sizeresult++;
            }
        } else {
            buffer[79] = '\n';
            buffer[80] = 0;
            sizeresult = 80;
        }

        // write output
        // ...
        verbose("%zd bytes output\n", sizeresult);
        fwrite(buffer, 1, sizeresult, stdout);
    }

    return retval;
}
