#ifndef TYPEINFO_H
#define TYPEINFO_H
#include "matrix.h"
#include <stdlib.h>

typedef struct Matrix Matrix;
typedef struct{
    size_t size;
    void (*sum)(const void* a, const void* b, void* out);
    void (*mull)(const void* a, const void* b, void* out);
    void (*plus)(const void* matrix1,const void*matrix2, void* rez);
    void (*multiplication)(const void* matrix1,const void*matrix2, void* rez);
    void (*scalar_multiplication)(const void* matrix1,const void* scalar, void* rez);
    void (*transponation)(const void* matrix, void* rez);
    Matrix* (*AddLinearCombination)(Matrix* matrix, int rowIndex, void* alphas);
    void (*print)(const void* matrix, int el);
}TypeInfo;
#endif //typeinfo.h
