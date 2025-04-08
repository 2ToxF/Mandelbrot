#include <stdio.h>

#include "cmd_processing.h"
#include "tests.h"
#include "window.h"


int main(int argc, char* argv[])
{
    int tests_number = 0;
    ProgramType prog_type = ReadCmd(argc, argv, &tests_number);

    switch (prog_type)
    {
        case DRAW:
            DrawMandelbrot();
            break;

        case TEST:
            RunTestsMandelbrot(tests_number);
            break;

        case UNKNOWN:
            printf("Sorry, met unknown flag\nAborting...\n");
            break;
    }


    return 0;
}
