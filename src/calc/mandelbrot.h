#ifndef MANDELBROT_H
#define MANDELBROT_H

const int MAX_DOT_TRIES = 256;

typedef struct __MandelbrotInfo
{
    unsigned int window_width;
    unsigned int window_height;

    float x_shift;
    float y_shift;
    float zoom;

    int* arr_iters;
} MandelbrotInfo;

void CalcMandelbrot(MandelbrotInfo* data);

#endif //MANDELBROT_H
