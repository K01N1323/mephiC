#include "matrix_operations.h"
#include "data.h"
#include <string.h>
#include <stdlib.h>

// Создает новую матрицу заданного типа и размера
Matrix* matrix_create(const TypeInfo* type, int rows, int cols){
    Matrix* m = malloc(sizeof(Matrix));
    if (!m) return NULL;
    
    m->rows = rows;
    m->cols = cols;
    m->typeinfo = type;
    
    // Инициализация методов матрицы универсальными функциями
    m->plus = generic_plus;
    m->multiplication = generic_multiplication;
    m->scalar_multiplication = generic_scalar_multiplication;
    m->transponation = generic_transponation;
    m->add_linear_combination = generic_add_linear_combination;
    m->print = generic_print;
    
    m->matrix = malloc((type->size) * cols * rows);
    if (!(m->matrix)) {
        free(m);
        return NULL;
    }
    
    return m;
}

// Освобождает память, выделенную под структуру матрицы и её данные
void matrix_free(Matrix* m){
    if (!m) return;
    free(m->matrix);
    free(m);
}

// Получает значение элемента по индексам строки и столбца
void matrix_get(const Matrix* m, int i, int j, void* out){
    if (i >= m->rows || j >= m->cols || i < 0 || j < 0) return;
    
    size_t sz = m->typeinfo->size;
    char* data = (char*)m->matrix;
    void* dat = data + (m->cols * i + j) * sz;
    
    memcpy(out, dat, sz);
}

// Копирует все элементы матрицы в предоставленный буфер
void matrix_getall(const Matrix* m, void* out){
    size_t total_sz = (m->typeinfo->size) * m->rows * m->cols;
    memcpy(out, m->matrix, total_sz);
}

// Перезаписывает элемент матрицы по заданному индексу
void matrix_set(Matrix* m, int i, int j, const void* value){
    if (i >= m->rows || j >= m->cols || i < 0 || j < 0) return;
    
    char* data = (char*)m->matrix;
    size_t sz = m->typeinfo->size;
    void* dat = data + (m->cols * i + j) * sz;
    
    memcpy(dat, value, sz);
}

// Заполняет всю матрицу переданными данными (массивом)
void matrix_setall(Matrix* m, const void* data){
    size_t total_sz = (m->typeinfo->size) * m->rows * m->cols;
    memcpy(m->matrix, data, total_sz);
}
