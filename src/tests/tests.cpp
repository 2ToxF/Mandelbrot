#include <immintrin.h>
#include <stdint.h>
#include <stdio.h>

#include "global_consts.h"
#include "mandelbrot.h"
#include "tests.h"

#ifdef TESTS
    static uint64_t CalcMandelbrotTime(MandelbrotInfo* data);

    void RunTestsMandelbrot()
    {
        MandelbrotInfo data = {};
        data.window_width   = WINDOW_WIDTH;
        data.window_height  = WINDOW_HEIGHT;
        data.x_shift        = DEFAULT_SHIFT_X;
        data.y_shift        = DEFAULT_SHIFT_Y;
        data.zoom           = DEFAULT_ZOOM;

        printf("%d\n", TESTS);
        for (int i = 0; i < TESTS; ++i)
            printf("%lu\n", CalcMandelbrotTime(&data));
    }


    static uint64_t CalcMandelbrotTime(MandelbrotInfo* data)
    {
        uint64_t start_time = __rdtsc();
        CalcMandelbrot(data);
        uint64_t end_time = __rdtsc();

        return end_time - start_time;
    }
#endif //TESTS
