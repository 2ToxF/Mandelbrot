#ifndef ARR_OPS_H
#define ARR_OPS_H

#define ArrAddArr(arr_dest, arr_src1, arr_src2, arr_size)\
{\
    for (int i = 0; i < arr_size; ++i)\
        arr_dest[i] = arr_src1[i] + arr_src2[i];\
}


#define ArrAddConst(arr_dest, arr_src, arr_size, term)\
{\
    for (int i = 0; i < arr_size; ++i)\
        arr_dest[i] = arr_src[i] + term;\
}


#define ArrAndConst(arr_dest, arr_src, arr_size, num)\
{\
    for (int i = 0; i < arr_size; ++i)\
        arr_dest[i] = arr_src[i] & num;\
}


#define ArrDivConst(arr_dest, arr_src, arr_size, divider)\
{\
    for (int i = 0; i < arr_size; ++i)\
        arr_dest[i] = arr_src[i] / divider;\
}


static inline int ArrGetMask(int arr[], int arr_size)\
{\
    int result = 0;\
    for (int i = 0; i < arr_size; ++i)\
        if (arr[i])\
            result |= 1 << i;\
    return result;\
}


#define ArrLtConst(arr_dest, arr_src, arr_size, num)\
{\
    for (int i = 0; i < arr_size; ++i)\
        arr_dest[i] = arr_src[i] < num ? 0xFFFFFFFF : 0;\
}


#define ArrMulArr(arr_dest, arr_src1, arr_src2, arr_size)\
{\
    for (int i = 0; i < arr_size; ++i)\
        arr_dest[i] = arr_src1[i] * arr_src2[i];\
}


#define ArrMulConst(arr_dest, arr_src, arr_size, factor)\
{\
    for (int i = 0; i < arr_size; ++i)\
        arr_dest[i] = arr_src[i] * factor;\
}


#define ArrSubArr(arr_dest, arr_src1, arr_src2, arr_size)\
{\
    for (int i = 0; i < arr_size; ++i)\
        arr_dest[i] = arr_src1[i] - arr_src2[i];\
}


#endif
