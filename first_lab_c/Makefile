CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g


program: main.c frontend.c complex_info.c double_info.c int_info.c data.c tests.c trash.c matrix_operations.c
	$(CC) $(CFLAGS) main.c frontend.c complex_info.c double_info.c int_info.c data.c tests.c trash.c matrix_operations.c -o program

clean:
	rm -f program
