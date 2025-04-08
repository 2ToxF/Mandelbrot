#include <immintrin.h>
// #include <stdio.h>
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
                    float x1_y1   = x1*y1;

                    if (x1_quad + y1_quad >= MAX_DISTANCE_QUAD)
                        break;

                    x1 = x1_quad - y1_quad + x0;
                    y1 = 2*x1_y1 + y0;
                }

                *(data->arr_iters + y*data->window_width + x) = n;
            }
        }
    }
#endif


// #define CALC_ARR_OPT
#ifdef CALC_ARR_OPT
    #define ARR_SIZE 4

    void CalcMandelbrotWithColors(MandelbrotInfo* data)
    {
        for (unsigned int y = 0; y < data->window_width; ++y)
        {
            float yf = (float) y / data->window_width * data->zoom + data->y_shift;
            float y0[ARR_SIZE] = {yf, yf, yf, yf};
            // float y0[ARR_SIZE] = {yf, yf, yf, yf, yf, yf, yf, yf};

            for (unsigned int x = 0; x < data->window_height; x += ARR_SIZE)
            {
                float xf = (float) x;
                float x0[ARR_SIZE] = {xf, xf+1, xf+2, xf+3};
                // float x0[ARR_SIZE] = {xf, xf+1, xf+2, xf+3, xf+4, xf+5, xf+6, xf+7};
                ArrDivConst(x0, x0, ARR_SIZE, (float) data->window_height);
                ArrMulConst(x0, x0, ARR_SIZE, data->zoom);
                ArrAddConst(x0, x0, ARR_SIZE, data->x_shift);

                float x1[ARR_SIZE]; memcpy(x1, x0, ARR_SIZE*sizeof(float));
                float y1[ARR_SIZE]; memcpy(y1, y0, ARR_SIZE*sizeof(float));

                int iters[ARR_SIZE] = {};
                for (int i = 0; i < MAX_DOT_TRIES; ++i)
                {
                    float x1_quad[ARR_SIZE]; ArrMulArr(x1_quad, x1,    x1,    ARR_SIZE);
                    float y1_quad[ARR_SIZE]; ArrMulArr(y1_quad, y1,    y1,    ARR_SIZE);
                    float x1_y1  [ARR_SIZE]; ArrMulArr(x1_y1,   x1,    y1,    ARR_SIZE);

                    float x1q_plus_y1q[ARR_SIZE]; ArrAddArr(x1q_plus_y1q, x1_quad, y1_quad, ARR_SIZE);
                    float x1_sub_x2   [ARR_SIZE]; ArrSubArr(x1_sub_x2,    x1_quad, y1_quad, ARR_SIZE);
                    float dx1_y1      [ARR_SIZE]; ArrAddArr(dx1_y1,       x1_y1,   x1_y1,   ARR_SIZE);

                    int cmp_quads[ARR_SIZE]; ArrLtConst(cmp_quads, x1q_plus_y1q, ARR_SIZE, MAX_DISTANCE_QUAD);
                    int cmp_mask = ArrGetMask(cmp_quads, ARR_SIZE);
                    if (!cmp_mask)
                        break;

                    ArrAndConst(cmp_quads, cmp_quads, ARR_SIZE, 1);
                    ArrAddArrInt(iters, iters, cmp_quads, ARR_SIZE);

                    ArrAddArr(x1, x1_sub_x2, x0, ARR_SIZE);

                    ArrAddArr(y1, dx1_y1, y0, ARR_SIZE);
                }

                memcpy(data->arr_iters + y*data->window_width + x, iters, ARR_SIZE*sizeof(int));
            }
        }
    }
#endif


#define CALC_INTR256_OPT
#ifdef CALC_INTR256_OPT
    #define INTR_SIZE_BYTES 8
    __m256  max_dist_quad   = _mm256_set1_ps(MAX_DISTANCE_QUAD);
    __m256i ones            = _mm256_set1_epi32(1);
    __m256  x_add           = _mm256_set_ps(7.f, 6.f, 5.f, 4.f, 3.f, 2.f, 1.f, 0.f);

    void CalcMandelbrotWithColors(MandelbrotInfo* data)
    {
        for (unsigned int y = 0; y < data->window_width; ++y)
        {
            float yf = (float) y / data->window_width * data->zoom + data->y_shift;
            __m256 y0 = _mm256_set1_ps(yf);

            for (unsigned int x = 0; x < data->window_height; x += INTR_SIZE_BYTES)
            {
                float xf = (float) x;
                __m256  x0 = _mm256_add_ps(_mm256_set1_ps(xf), x_add);
                        x0 = _mm256_div_ps(x0, _mm256_set1_ps((float) data->window_height));
                        x0 = _mm256_mul_ps(x0, _mm256_set1_ps(data->zoom));
                        x0 = _mm256_add_ps(x0, _mm256_set1_ps(data->x_shift));

                __m256 x1 = x0;
                __m256 y1 = y0;

                __m256i iters = _mm256_setzero_si256();
                for (int i = 0; i < MAX_DOT_TRIES; ++i)
                {
                    __m256 x1_quad = _mm256_mul_ps(x1, x1);
                    __m256 y1_quad = _mm256_mul_ps(y1, y1);
                    __m256 x1_y1   = _mm256_mul_ps(x1, y1);

                    __m256 x1q_plus_y1q = _mm256_add_ps(x1_quad, y1_quad);
                    __m256 x1_sub_x2    = _mm256_sub_ps(x1_quad, y1_quad);
                    __m256 dx1_y1       = _mm256_add_ps(x1_y1,   x1_y1  );

                    __m256 cmp_quads = _mm256_cmp_ps(x1q_plus_y1q, max_dist_quad, _CMP_LT_OQ);
                    int cmp_mask = _mm256_movemask_ps(cmp_quads);
                    if (!cmp_mask)
                        break;

                    iters = _mm256_add_epi32(iters, _mm256_and_si256(_mm256_castps_si256(cmp_quads), ones));

                    x1 = _mm256_add_ps(x1_sub_x2, x0);
                    y1 = _mm256_add_ps(dx1_y1,    y0);
                }

                memcpy(data->arr_iters + y*data->window_width + x, &iters, sizeof(__m256i));
            }
        }
    }
#endif
