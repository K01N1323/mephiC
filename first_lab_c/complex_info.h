#ifndef COMPLEX_INFO
#define COMPLEX_INFO
#include "matrix.h"
#include <stddef.h>
#include "data.h"
TypeInfo* GetComplexleInfo(void);
typedef struct{
    double re;
    double im;
}imagine;
#endif // complex_info

