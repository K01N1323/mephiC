#ifndef STRUCTURES_H
#define STRUCTURES_H
#include "typeinfo.h"

//(хранение даннфх через cols*i + j)
 struct Matrix{
    const TypeInfo* typeinfo;
    void* matrix;
    int rows;
    int cols;

    void (*plus)(const void* matrix1,const void*matrix2, void* rez);
    void (*multiplication)(const void* matrix1,const void*matrix2, void* rez);
    void (*scalar_multiplication)(const void* matrix1,const void* scalar, void* rez);
    void (*transponation)(const void* matrix, void* rez);
    Matrix* (*add_linear_combination)(Matrix* matrix, int rowIndex, void* alphas);
    void (*print)(const void* matrix, int el);
};
#endif // structures.h
