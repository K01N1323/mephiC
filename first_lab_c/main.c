#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "frontend.h"
#include "data.h"
#include "tests.h"

int main(void) {
    int choice;
    
    // Запуск автоматических тестов при старте
    start_auto_tests();
    
    // Основной цикл программы
    while (1) {
        print_menu();
        
        // Считывание выбора пользователя
        if (!(scanf("%d", &choice))) {
            printf("Вы ввели невалидное значение\n");
            return 0;
        }
        
        // Выполнение действия и выход, если actions возвращает 1
        if (actions(choice)) {
            break;
        }
    }
    
    return 0;
}
