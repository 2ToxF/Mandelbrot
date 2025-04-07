#ifndef ARR_OPS_H
#define ARR_OPS_H

void    ArrAddArr       (float arr_dest[], float arr_src1[], float arr_src2[], int arr_size);
void    ArrAddArrInt    (int arr_dest[], int arr_src1[], int arr_src2[], int arr_size);
void    ArrAddConst     (float arr_dest[], float arr_src[], int arr_size, float term);
void    ArrAndConst     (int arr_dest[], int arr_src[], int arr_size, int num);
void    ArrDivConst     (float arr_dest[], float arr_src[], int arr_size, float divider);
int     ArrGetMask      (int arr[], int arr_size);
void    ArrLtConst      (int arr_dest[], float arr_src[], int arr_size, float term);
void    ArrMulArr       (float arr_dest[], float arr_src1[], float arr_src2[], int arr_size);
void    ArrMulConst     (float arr_dest[], float arr_src[], int arr_size, float factor);
void    ArrSubArr       (float arr_dest[], float arr_src1[], float arr_src2[], int arr_size);

#endif
