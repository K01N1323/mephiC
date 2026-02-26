#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "frontend.h"
#include "data.h"
#include "tests.h"
int main(void){
    int choice;
    start_auto_tests();
    while (1) {
        print_menu();
        if (!(scanf("%d", &choice))){
            printf("Вы ввели невалидное значение\n");
            return 0;
        }
        if (actions(choice)) {
            break;
        }
    }
    return 0;
}




