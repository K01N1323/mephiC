CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

# Главная цель: программа зависит от всех исходных файлов
program: main.c frontend.c complex_info.c double_info.c int_info.c data.c tests.c trash.c
	$(CC) $(CFLAGS) main.c frontend.c complex_info.c double_info.c int_info.c data.c tests.c trash.c -o program

# Команда очистки для удаления скомпилированной программы
clean:
	rm -f program
