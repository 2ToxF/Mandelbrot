#ifndef ARR_OPS_H
#define ARR_OPS_H


static inline void ArrAddArr(float arr_dest[], float arr_src1[], float arr_src2[], int arr_size)
{
    for (int i = 0; i < arr_size; ++i)
        arr_dest[i] = arr_src1[i] + arr_src2[i];
}


static inline void ArrAddArrInt(int arr_dest[], int arr_src1[], int arr_src2[], int arr_size)
{
    for (int i = 0; i < arr_size; ++i)
        arr_dest[i] = arr_src1[i] + arr_src2[i];
}


static inline void ArrAddConst(float arr_dest[], float arr_src[], int arr_size, float term)
{
    for (int i = 0; i < arr_size; ++i)
        arr_dest[i] = arr_src[i] + term;
}


static inline void ArrAndConst(int arr_dest[], int arr_src[], int arr_size, int num)
{
    for (int i = 0; i < arr_size; ++i)
        arr_dest[i] = arr_src[i] & num;
}


static inline void ArrDivConst(float arr_dest[], float arr_src[], int arr_size, float divider)
{
    for (int i = 0; i < arr_size; ++i)
        arr_dest[i] = arr_src[i] / divider;
}


static inline int ArrGetMask(int arr[], int arr_size)
{
    int result = 0;
    for (int i = 0; i < arr_size; ++i)
        if (arr[i])
            result |= 1 << i;
    return result;
}


static inline void ArrLtConst(int arr_dest[], float arr_src[], int arr_size, float num)
{
    for (int i = 0; i < arr_size; ++i)
        arr_dest[i] = arr_src[i] < num ? 0xFFFFFFFF : 0;
}


static inline void ArrMulArr(float arr_dest[], float arr_src1[], float arr_src2[], int arr_size)
{
    for (int i = 0; i < arr_size; ++i)
        arr_dest[i] = arr_src1[i] * arr_src2[i];
}


static inline void ArrMulConst(float arr_dest[], float arr_src[], int arr_size, float factor)
{
    for (int i = 0; i < arr_size; ++i)
        arr_dest[i] = arr_src[i] * factor;
}


static inline void ArrSubArr(float arr_dest[], float arr_src1[], float arr_src2[], int arr_size)
{
    for (int i = 0; i < arr_size; ++i)
        arr_dest[i] = arr_src1[i] - arr_src2[i];
}


#endif //ARR_OPS_H
