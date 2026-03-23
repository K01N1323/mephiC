#ifndef DATA_H
#define DATA_H

#include "matrix.h"
#include "complex_info.h"
#include "int_info.h"
#include "double_info.h"
#include "bool_info.h"

// Создает новую матрицу заданного размера и типа
Matrix* matrix_create(const TypeInfo* type, int rows, int cols);

// Освобождает память, выделенную под матрицу
void matrix_free(Matrix* m);

// Получает элемент матрицы по индексам i и j и сохраняет в out
void matrix_get(const Matrix* m, int i, int j, void* out);

// Получает все данные матрицы и сохраняет их в out
void matrix_getall(const Matrix* m, void* out);

// Устанавливает значение элемента матрицы по индексам i и j
void matrix_set(Matrix* m, int i, int j, const void* value);

// Устанавливает все данные матрицы из массива data
void matrix_setall(Matrix* m, const void* data);

#endif //data.h
