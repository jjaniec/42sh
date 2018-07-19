all:
	gcc -Wall -Wextra -std=c11 -pedantic -O0  srcs/line_edition/*.c -L ft_printf/libft/ -lft -ltermcap -g  -o le
