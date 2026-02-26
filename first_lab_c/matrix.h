#ifndef STRUCTURES_H
#define STRUCTURES_H
#include "typeinfo.h"

//(хранение даннфх через cols*i + j)
 struct Matrix{
    TypeInfo* typeinfo;
    void* matrix;
    int rows;
    int cols;
};
#endif // structures.h
