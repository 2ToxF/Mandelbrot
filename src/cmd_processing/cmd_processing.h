#ifndef CMD_PROCESSING_H
#define CMD_PROCESSING_H

enum ProgramType
{
    DRAW,
    TEST,
    UNKNOWN,
};

ProgramType ReadCmd(int argc, char* argv[], int* tests_number_p);

#endif //CMD_PROCESSING_H
