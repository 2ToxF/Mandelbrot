#include <stdio.h>
#include <typeinfo>

#include "calc/mandelbrot.h"

const float MAX_DISTANCE_QUAD = 100.0;


void CalcMandelbrot(MandelbrotInfo* data)
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
