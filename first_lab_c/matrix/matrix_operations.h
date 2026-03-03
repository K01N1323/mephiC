#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

#include "matrix.h"

void generic_plus(const void* matrix1, const void* matrix2, void* rez);
void generic_multiplication(const void* matrix1, const void* matrix2, void* rez);
void generic_scalar_multiplication(const void* matrix1, const void* scalar, void* rez);
void generic_transponation(const void* matrix, void* rez);
Matrix* generic_add_linear_combination(Matrix* matrix, int rowIndex, void* alphas);
void generic_print(const void* matrix, int el);

#endif // MATRIX_OPERATIONS_H
