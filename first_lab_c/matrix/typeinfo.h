#ifndef TYPEINFO_H
#define TYPEINFO_H
#include "matrix.h"
#include <stddef.h>

typedef struct Matrix Matrix;

// Структура, хранящая функции и метаданные для специфичного типа элементов матрицы
typedef struct {
    size_t size;                                           // Размер одного элемента в байтах
    void (*sum)(const void* a, const void* b, void* out);  // Функция сложения двух элементов
    void (*mull)(const void* a, const void* b, void* out); // Функция умножения двух элементов
    void (*print_element)(const void* elem);               // Функция вывода элемента на экран
} TypeInfo;

#endif //typeinfo.h
