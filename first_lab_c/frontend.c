#include "frontend.h"
#include <stdio.h>
#include "matrix.h"
#include "data.h"
#include "complex_info.h"
#include "int_info.h"
#include "double_info.h"
#include <string.h>
#include <stdlib.h>
#define max_matrices 50
static Matrix* matrices[max_matrices];
static int matrices_count = 0;
void print_menu(void){
    printf("Выберите действие: ");
    printf("1 – создать int матрицу\n");
    printf("2 – создать double матрицу\n");
    printf("3 – создать complex матрицу\n");
    printf("4 – вывести матрицу\n");
    printf("5 – вывести элемент матрицы\n");
    printf("6 – сетнуть элемент матрицы\n");
    printf("7 – сложить две матрицы \n");
    printf("8 – умножить две матрицы\n");
    printf("9 – умножить матрицу на скаляр\n");
    printf("10 – транспонировать матрицу\n");
    printf("11 – очистить матрицу\n");
    printf("12 - посчитать прибавление к строке линейной комбинации других строк\n");
    printf("13 - вывести номера матриц, доступных для взаимодействия \n");
    printf("-1 – выйти из программы\n");
}
int actions(int flag){
    int rows, cols, num, num_element, i, j;
    switch (flag) {
        case -1: {
            for (int i = 0; i < matrices_count; i++) {
                matrix_free(matrices[i]);
            }
            return 1;
        }
        case 1: {
            printf("Введите количество строк и рядов в матрице: ");
            scanf("%d %d", &rows, &cols);
            TypeInfo* type = GetIntInfo();
            Matrix* new_matrix = matrix_create(type, rows, cols);
            if (matrices_count < max_matrices){
                matrices[matrices_count] = new_matrix;
                printf("Матрица создана под номером %d\n", matrices_count);
                matrices_count++;
            }else {
                printf("Нет места для новой матрицы\n");
                matrix_free(new_matrix);
            }
            break;
        }
        case 2: {
            printf("Введите количество строк и рядов в матрице: ");
            scanf("%d %d", &rows, &cols);
            TypeInfo* type = GetDoubleInfo();
            Matrix* new_matrix = matrix_create(type, rows, cols);
            if (matrices_count < max_matrices){
                matrices[matrices_count] = new_matrix;
                printf("Матрица создана под номером %d\n", matrices_count);
                matrices_count++;
            }else {
                printf("Нет места для новой матрицы\n");
                matrix_free(new_matrix);
            }
            break;
        }
        case 3: {
            printf("Введите количество строк и рядов в матрице: ");
            scanf("%d %d", &rows, &cols);
            TypeInfo* type = GetComplexleInfo();
            Matrix* new_matrix = matrix_create(type, rows, cols);
            if (matrices_count < max_matrices){
                matrices[matrices_count] = new_matrix;
                printf("Матрица создана под номером %d\n", matrices_count);
                matrices_count++;
            }else {
                printf("Нет места для новой матрицы\n");
                matrix_free(new_matrix);
            }
            break;
        }
        case 4: {
            printf("Введите номер матрицы, которую вы хотите вывести на экран: ");
            scanf("%d", &num);
            num_element = -1;
            if (num < 0 || num >= matrices_count || matrices[num] == NULL){
                printf("Матрицы с таким номером нет\n");
            }else{
                Matrix* current_matrix = matrices[num];
                current_matrix->typeinfo->print(current_matrix, num_element);
            }
            break;
        }
        case 5: {
            printf("Введите номер матрицы и номер элемента, который вы хотите вывести на экран: ");
            scanf("%d %d", &num, &num_element);
            if (num < 0 || num >= matrices_count || matrices[num] == NULL){
                printf("Матрицы с таким номером нет\n");
            }else{
                Matrix* current_matrix = matrices[num];
                current_matrix->typeinfo->print(current_matrix, num_element);
            }
            break;
        }
        case 6: {
            printf("Введите номер матрицы и номер строки и столбца элемента, который вы хотите сетнуть: ");
            scanf("%d %d %d", &num, &i, &j);
            Matrix* m = matrices[num];
            if (!m){
                printf("Матрицы с таким номером нет\n");
            }else if (i >= m->rows || j >= m->cols || i < 0 || j < 0){
                printf("Элементов под таким номером в матрице нет");
            }else if (m->typeinfo == GetIntInfo()) {
                int v;
                printf("Введите int: ");
                scanf("%d", &v);
                matrix_set(m, i, j, &v);
            }else if (m->typeinfo == GetDoubleInfo()) {
                double v;
                printf("Введите double: ");
                scanf("%lf", &v);
                matrix_set(m, i, j, &v);
            }else if (m->typeinfo == GetComplexleInfo()) {
                imagine v;
                printf("Введите действительную и мнимую части: ");
                scanf("%lf %lf", &v.re, &v.im);
                matrix_set(m, i, j, &v);
            }
            break;
        }
        case 7: {
            printf("Введите номера матриц, которые вы хотите сложить: ");
            scanf("%d %d", &i, &j);
            if (i < 0 || j < 0 || i >= matrices_count || j >= matrices_count ||
                matrices[i] == NULL || matrices[j] == NULL) {
                printf("Матриц с таким номером не существует\n");
            } else {
                Matrix* a = matrices[i];
                Matrix* b = matrices[j];
                if (a->typeinfo != b->typeinfo) {
                    printf("Нельзя сложить матрицы разных типов\n");
                    return 0;
                }
                if (a->rows != b->rows || a->cols != b->cols) {
                    printf("Размеры матриц не совпадают\n");
                    return 0;
                }
                if (matrices_count >= max_matrices) {
                    printf("Нет места для новой матрицы\n");
                    return 0;
                }
                Matrix* c = matrix_create(a->typeinfo, a->rows, a->cols);
                a->typeinfo->plus(a, b, c);
                matrices[matrices_count] = c;
                printf("Результат сложения записан в матрицу под номером %d\n", matrices_count);
                matrices_count++;
            }
            break;
        }
        case 8: {
            printf("Введите номера матриц, которые вы хотите перемножить: ");
            scanf("%d %d", &i, &j);
            if (i < 0 || j < 0 || i >= matrices_count || j >= matrices_count ||
                matrices[i] == NULL || matrices[j] == NULL) {
                printf("Матриц с таким номером не существует\n");
                return 0;
            }
            Matrix* a = matrices[i];
            Matrix* b = matrices[j];
            if (a->typeinfo != b->typeinfo) {
                printf("Нельзя перемножить матрицы разных типов\n");
                return 0;
            }
            if (a->cols != b->rows) {
                printf("Нельзя перемножить матрицы с такими размерами\n");
                return 0;
            }
            if (matrices_count >= max_matrices) {
                printf("Нет места для новой матрицы\n");
                return 0;
            }
            Matrix* c = matrix_create(a->typeinfo, a->rows, b->cols);
            a->typeinfo->multiplication(a, b, c);
            matrices[matrices_count] = c;
            printf("Результат умножения записан в матрицу под номером %d\n", matrices_count);
            matrices_count++;
            break;
        }
        case 9: {
            printf("Введите номер матрицы, которую вы хотите умножить на скаляр: ");
            scanf("%d", &num);
            if (num < 0 || num >= matrices_count || matrices[num] == NULL){
                printf("Матрицы с таким номером не существует\n");
                return 0;
            }
            Matrix* m = matrices[num];
            if (matrices_count >= max_matrices){
                printf("Нет места для новой матрицы\n");
                return 0;
            }
            Matrix* r = matrix_create(m->typeinfo, m->rows, m->cols);
            if (m->typeinfo == GetIntInfo()){
                int sc;
                printf("Введите int‑скаляр: ");
                scanf("%d", &sc);
                m->typeinfo->scalar_multiplication(m, &sc, r);
            } else if (m->typeinfo == GetDoubleInfo()){
                double sc;
                printf("Введите double‑скаляр: ");
                scanf("%lf", &sc);
                m->typeinfo->scalar_multiplication(m, &sc, r);
            } else if (m->typeinfo == GetComplexleInfo()){
                imagine sc;
                printf("Введите действительную и мнимую части скаляра: ");
                scanf("%lf %lf", &sc.re, &sc.im);
                m->typeinfo->scalar_multiplication(m, &sc, r);
            } else {
                printf("Неизвестный тип матрицы\n");
                matrix_free(r);
                return 0;
            }
            matrices[matrices_count] = r;
            printf("Результат умножения на скаляр записан в матрицу под номером %d\n", matrices_count);
            matrices_count++;
            break;
        }
        case 10: {
            printf("Введите номер матрицы, которую вы хотите транспонировать: ");
            scanf("%d", &num);
            if (num < 0 || num >= matrices_count || matrices[num] == NULL) {
                printf("Матрицы с таким номером не существует\n");
                return 0;
            }
            Matrix* m = matrices[num];
            if (matrices_count >= max_matrices) {
                printf("Нет места для новой матрицы\n");
                return 0;
            }
            Matrix* t = matrix_create(m->typeinfo, m->cols, m->rows);
            m->typeinfo->transponation(m, t);
            matrices[matrices_count] = t;
            printf("Результат транспонирования записан в матрицу под номером %d\n", matrices_count);
            matrices_count++;
            break;
        }
        case 11: {
            printf("Введите номер матрицы, которую вы хотите удалить");
            scanf("%d", &num);
            if (num >= matrices_count || num < 0 || matrices[num] == NULL){
                printf("Матрицы под таким номером не существует");
                return 0;
            }
            matrix_free(matrices[num]);
            matrices[num] = NULL;
            break;
        }
        case 12: {
            printf("Введите номер изменяемой матрицы: ");
            scanf("%d", &num);

            if (num < 0 || num >= matrices_count || matrices[num] == NULL) {
                printf("Матрицы с таким номером не существует\n");
                return 0;
            }
            Matrix* m = matrices[num];
            int rows = m->rows;

            printf("Введите индекс изменяемой строки: ");
            int rowIndex;
            scanf("%d", &rowIndex);

            if (rowIndex < 0 || rowIndex >= rows) {
                printf("Неверный индекс строки\n");
                return 0;
            }

            if (matrices_count >= max_matrices) {
                printf("Нет места для новой матрицы\n");
                return 0;
            }

            int coef_count = rows - 1;
            Matrix* result = NULL;

            if (m->typeinfo == GetIntInfo()) {
                int* alphas = malloc(coef_count * sizeof(int));
                printf("Введите %d int-коэффициентов (для каждой строки кроме %d):\n",
                       coef_count, rowIndex);
                for (int k = 0; k < coef_count; k++) {
                    scanf("%d", &alphas[k]);
                }
                result =  m->typeinfo->AddLinearCombination(m, rowIndex, alphas);
                free(alphas);
            } else if (m->typeinfo == GetDoubleInfo()) {
                double* alphas = malloc(coef_count * sizeof(double));
                printf("Введите %d double-коэффициентов (для каждой строки кроме %d):\n",
                       coef_count, rowIndex);
                for (int k = 0; k < coef_count; k++) {
                    scanf("%lf", &alphas[k]);
                }
                result = m->typeinfo->AddLinearCombination(m, rowIndex, alphas);
                free(alphas);
            } else if (m->typeinfo == GetComplexleInfo()) {
                imagine* alphas = malloc(coef_count * sizeof(imagine));
                printf("Введите %d complex-коэффициентов (для каждой строки кроме %d):\n",
                       coef_count, rowIndex);
                for (int k = 0; k < coef_count; k++) {
                    scanf("%lf %lf", &alphas[k].re, &alphas[k].im);
                }
                result =  m->typeinfo->AddLinearCombination(m, rowIndex, alphas);
                free(alphas);
            }
            matrices[matrices_count] = result;
            printf("Результат записан в матрицу под номером %d\n", matrices_count);
            matrices_count++;
            break;
        }
        case 13:{
            if (matrices_count == 0) printf("Нет доступных для взаимодействия матриц\n");
            printf("Доступные для взаимодействия матрицы: ");
            for (int index = 0; index < matrices_count; index++){
                if (matrices[index] != NULL) printf("%d ", index);
            }
            printf("\n");
            break;
        }
        default: {
            printf("Команда, которую вы ввели не существует\n");
            break;
        }
    }
    return 0;
}

