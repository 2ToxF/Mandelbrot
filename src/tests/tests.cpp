#include <stdio.h>

#include "global_consts.h"
#include "mandelbrot.h"
#include "tests.h"

const int DIFFERENT_TESTS_NUMBER = 100;


void RunTestsMandelbrot(int tests_number)
{
    MandelbrotInfo data = {};
    data.window_width   = WINDOW_WIDTH;
    data.window_height  = WINDOW_HEIGHT;
    data.x_shift        = DEFAULT_SHIFT_X;
    data.y_shift        = DEFAULT_SHIFT_Y;
    data.zoom           = DEFAULT_ZOOM;

    printf("%d %d\n", DIFFERENT_TESTS_NUMBER, tests_number);
    for (int i = 0; i < DIFFERENT_TESTS_NUMBER; ++i)
    {
        for (int j = 0; j < tests_number; ++j)
            printf("%d %d %lu\n", i, j, CalcMandelbrotWithTime(&data));

        data.zoom /= 1.01;
        data.x_shift = 0.005 * data.zoom + data.x_shift;
        data.y_shift = 0.005 * data.zoom + data.y_shift;
    }
}
