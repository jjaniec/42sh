
all:
	gcc -Wall -Wextra -std=c11 -pedantic -O0 -g srcs/line_edition/*.c -L ft_printf/libft/ -lft -ltermcap   -o le