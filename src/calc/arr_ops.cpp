#include "arr_ops.h"


void ArrAddArr(float arr_dest[], float arr_src1[], float arr_src2[], int arr_size)
{
    for (int i = 0; i < arr_size; ++i)
        arr_dest[i] = arr_src1[i] + arr_src2[i];
}


void ArrAddArrInt(int arr_dest[], int arr_src1[], int arr_src2[], int arr_size)
{
    for (int i = 0; i < arr_size; ++i)
        arr_dest[i] = arr_src1[i] + arr_src2[i];
}


void ArrAddConst(float arr_dest[], float arr_src[], int arr_size, float term)
{
    for (int i = 0; i < arr_size; ++i)
        arr_dest[i] = arr_src[i] + term;
}


void ArrAndConst(int arr_dest[], int arr_src[], int arr_size, int num)
{
    for (int i = 0; i < arr_size; ++i)
        arr_dest[i] = arr_src[i] & num;
}


void ArrDivConst(float arr_dest[], float arr_src[], int arr_size, float divider)
{
    for (int i = 0; i < arr_size; ++i)
        arr_dest[i] = arr_src[i] / divider;
}


int ArrGetMask(int arr[], int arr_size)
{
    int result = 0;
    for (int i = 0; i < arr_size; ++i)
        if (arr[i])
            result |= 1 << i;
    return result;
}


void ArrLtConst(int arr_dest[], float arr_src[], int arr_size, float term)
{
    for (int i = 0; i < arr_size; ++i)
        arr_dest[i] = arr_src[i] < term ? 0xFFFFFFFF : 0;
}


void ArrMulArr(float arr_dest[], float arr_src1[], float arr_src2[], int arr_size)
{
    for (int i = 0; i < arr_size; ++i)
        arr_dest[i] = arr_src1[i] * arr_src2[i];
}


void ArrMulConst(float arr_dest[], float arr_src[], int arr_size, float factor)
{
    for (int i = 0; i < arr_size; ++i)
        arr_dest[i] = arr_src[i] * factor;
}


void ArrSubArr(float arr_dest[], float arr_src1[], float arr_src2[], int arr_size)
{
    for (int i = 0; i < arr_size; ++i)
        arr_dest[i] = arr_src1[i] - arr_src2[i];
}
