# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/05 18:15:37 by jjaniec           #+#    #+#              #
#    Updated: 2018/12/10 19:50:26 by cgaspart         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC_NAME = ft_apply_attr_.c \
           ft_apply_attributes.c \
           ft_apply_options.c \
           ft_apply_precision.c \
           ft_apply_width.c \
           ft_atoi_hex.c \
           ft_char_to_str.c \
           ft_convert_arg_mod_.c \
           ft_convert_arg_mod_2.c \
           ft_convert_arg_modifiers.c \
           ft_convert_arg_no_modifiers.c \
           ft_count_args.c \
           ft_create_arglist.c \
           ft_create_elem.c \
           ft_debug_args.c \
           ft_free_elem.c \
           ft_generate_width.c \
           ft_get_flag.c \
           ft_is_color.c \
           ft_imax_toa.c \
           ft_is_conv_numeric.c \
           ft_is_flag.c \
           ft_parse_attributes.c \
           ft_parse_modifiers.c \
           ft_parse_precision.c \
           ft_parse_width.c \
           ft_print_color.c \
           ft_print_color_id.c \
           ft_print_next_arg.c \
           ft_print_until_validconv.c \
           ft_printf.c \
           ft_printf_no_args.c \
           ft_printf_percent.c \
           ft_printf_str_arg.c \
           ft_putchar_printf.c \
           ft_putstr_hex.c \
           ft_putwchar.c \
           ft_putwstr.c \
           ft_sizeof_wstr_to_char.c \
           ft_strnotchr.c \
           ft_uitoa_base.c \
           ft_voidptr_to_hex.c \
           ft_wchar_byte_to_char.c \
           ft_wchar_masklen.c \
           ft_wchar_t_to_str.c \
           ft_wchar_tptr_to_str.c

OBJS_NAMES = $(OBJS_NAMES:.c=.o)

CC = gcc
C_FLAGS = -Wall -Wextra -Werror
IFLAGS = -I./libft -I./$(INCLUDES_DIR)
LFLAGS = -L./libft/ -lft
LINUX_FLAGS = -fPIC -std=c99 -Wno-pointer-arith -Wno-pointer-to-int-cast -Wno-type-limits -Wno-cast-function-type
SRC_DIR = ./srcs/
OBJ_DIR = ./objs/
INCLUDES_DIR = ./includes/

SRCS = $(addprefix $(SRC_DIR), $(SRC_NAME))
OBJS = $(addprefix $(OBJ_DIR), $(SRC_NAME:.c=.o))

LIBFT_DIR = ./libft
LIBFT = $(addprefix $(LIBFT_DIR),"/libft.a")

MAKEFILE_STATUS = $(addprefix $(LIBFT_DIR),"/.makefile_status.sh")

UNAME_S := $(shell uname -s)

define ui_line
    $(MAKEFILE_STATUS) $(1) $(2) || true
endef

all : $(NAME)

$(NAME) : $(LIBFT) $(OBJS)
ifeq ($(UNAME_S),Linux)
	@ar rcs $(NAME) $(OBJS) $(LIBFT_DIR)/objs/*.o
endif
ifeq ($(UNAME_S),Darwin)
	@ar rcs $(NAME)_ $(OBJS)
	@libtool -static -o $(NAME) $(NAME)_ $(LIBFT)
	@rm -f $(NAME)_
endif

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR) 2> /dev/null || true
ifeq ($(UNAME_S),Linux)
	@$(CC) $(C_FLAGS) $(LINUX_FLAGS) $(IFLAGS) -c $^ -o $@ && $(call ui_line, $@, $(NAME))
endif
ifeq ($(UNAME_S),Darwin)
	@$(CC) $(C_FLAGS) $(IFLAGS) -c $^ -o $@ && $(call ui_line, $@ $(NAME))
endif

clean:
	@rm -f $(OBJ)
	@rm -rf $(OBJ_DIR)
	@make clean -C libft/

fclean: clean
	@make fclean -C libft/
	@rm -f $(NAME)

$(LIBFT):
	@make -C ./libft/

re: fclean all

.PHONY : clean re tests curqui_test all
