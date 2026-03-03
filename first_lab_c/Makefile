CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -Imatrix -Itypes -Ifrontend -Itests

SRCS = main.c frontend/frontend.c types/complex_info.c types/double_info.c types/int_info.c types/bool_info.c matrix/data.c tests/tests.c matrix/matrix_operations.c

program: $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o program

clean:
	rm -f program
