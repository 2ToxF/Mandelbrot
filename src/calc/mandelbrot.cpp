#include <stdio.h>
#include <string.h>

#include "arr_ops.h"
#include "mandelbrot.h"

const float MAX_DISTANCE_QUAD = 100.0;

// #define CALC_NO_OPT
#ifdef CALC_NO_OPT
    void CalcMandelbrotWithColors(MandelbrotInfo* data)
    {
        for (unsigned int y = 0; y < data->window_width; ++y)
        {
            float y0 = (float) y / data->window_width * data->zoom + data->y_shift;
            for (unsigned int x = 0; x < data->window_height; ++x)
            {
                float x0 = (float) x / data->window_height * data->zoom + data->x_shift;

                float x1 = x0;
                float y1 = y0;

                int n = 0;
                for (; n < MAX_DOT_TRIES; ++n)
                {
                    float x1_quad = x1*x1;
                    float y1_quad = y1*y1;

                    if (x1_quad + y1_quad >= MAX_DISTANCE_QUAD)
                        break;

                    float x1_y1 = x1*y1;
                    x1 = x1_quad - y1_quad + x0;
                    y1 = 2*x1_y1 + y0;
                }

                *(data->arr_iters + y*data->window_width + x) = n;
            }
        }
    }
#endif


#define CALC_ARR_OPT
#ifdef CALC_ARR_OPT
    const int ARR_SIZE = 4;

    void CalcMandelbrotWithColors(MandelbrotInfo* data)
    {
        for (unsigned int y = 0; y < data->window_width; ++y)
        {
            float yf = (float) y;
            float y0[ARR_SIZE] = {yf, yf, yf, yf};
            ArrDivConst(y0, y0, ARR_SIZE, data->window_width);
            ArrMulConst(y0, y0, ARR_SIZE, data->zoom);
            ArrAddConst(y0, y0, ARR_SIZE, data->y_shift);

            for (unsigned int x = 0; x < data->window_height / ARR_SIZE; ++x)
            {
                float xf = (float) x*ARR_SIZE;
                float x0[ARR_SIZE] = {xf, xf+1, xf+2, xf+3};
                ArrDivConst(x0, x0, ARR_SIZE, data->window_height);
                ArrMulConst(x0, x0, ARR_SIZE, data->zoom);
                ArrAddConst(x0, x0, ARR_SIZE, data->x_shift);

                float x1[ARR_SIZE] = {}; memcpy(x1, x0, ARR_SIZE*sizeof(float));
                float y1[ARR_SIZE] = {}; memcpy(y1, y0, ARR_SIZE*sizeof(float));

                int n[ARR_SIZE] = {};
                for (int i = 0; i < MAX_DOT_TRIES; ++i)
                {
                    float x1_quad[ARR_SIZE]; ArrMulArr(x1_quad, x1,    x1,    ARR_SIZE);
                    float y1_quad[ARR_SIZE]; ArrMulArr(y1_quad, y1,    y1,    ARR_SIZE);
                    float x1_y1  [ARR_SIZE]; ArrMulArr(x1_y1,   x1,    y1,    ARR_SIZE);
                    float dx1_y1 [ARR_SIZE]; ArrAddArr(x1_y1,   x1_y1, x1_y1, ARR_SIZE);

                    float x1q_plus_y1q[ARR_SIZE]; ArrAddArr(x1q_plus_y1q, x1_quad, y1_quad, ARR_SIZE);
                    int   cmp_quads[ARR_SIZE];    ArrLtConst(cmp_quads, x1q_plus_y1q, ARR_SIZE, MAX_DISTANCE_QUAD);

                    int cmp_mask = ArrGetMask(cmp_quads, ARR_SIZE);
                    if (!cmp_mask)
                        break;

                    ArrAndConst(cmp_quads, cmp_quads, ARR_SIZE, 1);
                    ArrAddArrInt(n, n, cmp_quads, ARR_SIZE);

                    float x1_sub_x2[ARR_SIZE]; ArrSubArr(x1_sub_x2, x1_quad, y1_quad, ARR_SIZE);
                    ArrAddArr(x1, x1_sub_x2, x0, ARR_SIZE);

                    ArrAddArr(y1, dx1_y1, y0, ARR_SIZE);
                }

                memcpy(data->arr_iters + y*data->window_width + x * ARR_SIZE, n, ARR_SIZE*sizeof(int));
            }
        }
    }
#endif
