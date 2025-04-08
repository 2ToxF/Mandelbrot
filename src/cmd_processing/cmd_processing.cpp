#include <stdio.h>
#include <string.h>

#include "cmd_processing.h"

const char  DRAW_CMD[]              = "--draw";
const char  TESTS_CMD[]             = "--tests";

const int   DEFAULT_TESTS_NUMBER    = 1000;


ProgramType ReadCmd(int argc, char* argv[], int* tests_number_p)
{
    *tests_number_p = DEFAULT_TESTS_NUMBER;
    ProgramType prog_type = DRAW;

    for (int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], DRAW_CMD) == 0)
            prog_type = DRAW;

        else if (strcmp(argv[i], TESTS_CMD) == 0)
        {
            sscanf(argv[i], "%*s=%d", tests_number_p);
            prog_type = TEST;
        }

        else
            return UNKNOWN;
    }

    return prog_type;
}
