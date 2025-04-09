#include <stdio.h>

#include "global_consts.h"
#include "mandelbrot.h"
#include "tests.h"


void RunTestsMandelbrot(int tests_number)
{
    MandelbrotInfo data = {};
    data.window_width   = WINDOW_WIDTH;
    data.window_height  = WINDOW_HEIGHT;
    data.x_shift        = DEFAULT_SHIFT_X;
    data.y_shift        = DEFAULT_SHIFT_Y;
    data.zoom           = DEFAULT_ZOOM;

    printf("%d\n", tests_number);
    for (int i = 0; i < tests_number; ++i)
        printf("%d %lu\n", i, CalcMandelbrotWithTime(&data));
}
