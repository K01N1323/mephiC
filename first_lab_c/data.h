#ifndef DATA_H
#define DATA_H
#include "matrix.h"
#include "complex_info.h"
#include "int_info.h"
#include "double_info.h"
Matrix* matrix_create(const TypeInfo* type, int rows, int cols);
void matrix_free(Matrix* m);
// геттеры для элемента и целой матрицы
void matrix_get(const Matrix *m, int i, int j, void* out);
void matrix_getall(const Matrix* m, void* out);
// сеттеры для элемента и матрицы
void matrix_set(Matrix *m, int i, int j, const void* value);
void matrix_setall(Matrix *m, const void* data);
#endif //data.h

