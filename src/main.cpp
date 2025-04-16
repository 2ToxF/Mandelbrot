#include <stdio.h>

#include "tests.h"
#include "window.h"


int main()
{
    #if defined(DRAW)
        DrawMandelbrot();
    #elif defined(TESTS)
        RunTestsMandelbrot();
    #endif

    return 0;
}
