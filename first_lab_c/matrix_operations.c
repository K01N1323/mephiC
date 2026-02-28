#include "matrix_operations.h"
#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generic_plus(const void* matrix1, const void* matrix2, void* rez) {
    const Matrix* m1 = (const Matrix*)matrix1;
    const Matrix* m2 = (const Matrix*)matrix2;
    Matrix* r = (Matrix*)rez;
    
    if (m1->typeinfo != m2->typeinfo) return;
    if (m1->rows != m2->rows || m1->cols != m2->cols) return;
    if (r->rows != m1->rows || r->cols != m1->cols) return;

    size_t sz = m1->typeinfo->size;
    char* a = (char*)m1->matrix;
    char* b = (char*)m2->matrix;
    char* re = (char*)r->matrix;
    
    for (int row = 0; row < m1->rows; ++row) {
        for (int col = 0; col < m1->cols; ++col) {
            int ind = row * m1->cols + col;
            m1->typeinfo->sum(a + ind * sz, b + ind * sz, re + ind * sz);
        }
    }
}

void generic_multiplication(const void* matrix1, const void* matrix2, void* rez) {
    const Matrix* m1 = (const Matrix*)matrix1;
    const Matrix* m2 = (const Matrix*)matrix2;
    Matrix* r = (Matrix*)rez;

    if (m1->typeinfo != m2->typeinfo) return;
    if (m1->cols != m2->rows) return;
    if (r->rows != m1->rows || r->cols != m2->cols) return;

    size_t sz = m1->typeinfo->size;
    char* a = (char*)m1->matrix;
    char* b = (char*)m2->matrix;
    char* rez_matrix = (char*)r->matrix;
    
    void* sum = malloc(sz);
    void* prod = malloc(sz);
    
    for (int row = 0; row < m1->rows; ++row) {
        for (int col = 0; col < m2->cols; ++col) {
            memset(sum, 0, sz);
            for (int k = 0; k < m1->cols; ++k) {
                m1->typeinfo->mull(a + (row * m1->cols + k) * sz, b + (k * m2->cols + col) * sz, prod);
                m1->typeinfo->sum(sum, prod, sum);
            }
            memcpy(rez_matrix + (row * m2->cols + col) * sz, sum, sz);
        }
    }
    free(sum);
    free(prod);
}

void generic_scalar_multiplication(const void* matrix1, const void* scalar, void* rez) {
    const Matrix* m1 = (const Matrix*)matrix1;
    Matrix* r = (Matrix*)rez;
    
    if (r->rows != m1->rows || r->cols != m1->cols) return;

    size_t sz = m1->typeinfo->size;
    char* mat = (char*)m1->matrix;
    char* rez_matrix = (char*)r->matrix;
    
    for (int row = 0; row < m1->rows; ++row) {
        for (int col = 0; col < m1->cols; ++col) {
            int ind = row * m1->cols + col;
            m1->typeinfo->mull(mat + ind * sz, scalar, rez_matrix + ind * sz);
        }
    }
}

void generic_transponation(const void* matrix, void* rez) {
    const Matrix* m = (const Matrix*)matrix;
    Matrix* r = (Matrix*)rez;
    
    if (r->rows != m->cols || r->cols != m->rows) return;

    size_t sz = m->typeinfo->size;
    char* mat = (char*)m->matrix;
    char* rez_matrix = (char*)r->matrix;
    
    for (int row = 0; row < m->rows; ++row) {
        for (int col = 0; col < m->cols; ++col) {
            memcpy(rez_matrix + (col * r->cols + row) * sz, 
                   mat + (row * m->cols + col) * sz, sz);
        }
    }
}

Matrix* generic_add_linear_combination(Matrix* matrix, int rowIndex, void* alphas) {
    size_t sz = matrix->typeinfo->size;
    char* m1 = (char*)matrix->matrix;
    char* alph = (char*)alphas;
    
    Matrix* rezult = matrix_create((TypeInfo*)matrix->typeinfo, matrix->rows, matrix->cols);
    if (!rezult) return NULL;
    memcpy(rezult->matrix, m1, matrix->rows * matrix->cols * sz);
    char* rezult_matrix = (char*)rezult->matrix;
    
    void* prod = malloc(sz);
    int current_koof;
    
    for (int col = 0; col < matrix->cols; ++col) {
        current_koof = 0;
        for (int row = 0; row < matrix->rows; ++row) {
            if (row == rowIndex) continue;
            
            matrix->typeinfo->mull(rezult_matrix + (row * matrix->cols + col) * sz, alph + current_koof * sz, prod);
            matrix->typeinfo->sum(rezult_matrix + (rowIndex * matrix->cols + col) * sz,  prod,  rezult_matrix + (rowIndex * matrix->cols + col) * sz);
            ++current_koof;
        }
    }
    free(prod);
    return rezult;
}

void generic_print(const void* matrix, int el) {
    const Matrix* m = (const Matrix*)matrix;
    size_t sz = m->typeinfo->size;
    char* mat = (char*)m->matrix;
    int total = m->rows * m->cols;
    
    if (el >= 0) {
        if (el >= total) return;
        m->typeinfo->print_element(mat + el * sz);
        printf("\n");
        return;
    }
    
    for (int row = 0; row < m->rows; ++row) {
        for (int col = 0; col < m->cols; ++col) {
            m->typeinfo->print_element(mat + (row * m->cols + col) * sz);
            printf(" ");
        }
        printf("\n");
    }
}
