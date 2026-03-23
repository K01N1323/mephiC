#ifndef COMPLEX_INFO
#define COMPLEX_INFO

#include "matrix.h"

// Возвращает структуру с информацией о типе для комплексных чисел
const TypeInfo* GetComplexleInfo(void);

// Структура для хранения комплексного числа (вещественная и мнимая части)
typedef struct {
    double re;
    double im;
} imagine;

#endif // complex_info
