# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/05 21:53:56 by jjaniec           #+#    #+#              #
#    Updated: 2018/06/11 18:15:48 by jjaniec          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 42sh

UNAME_S := $(shell uname -s)

SRC_NAME = 	main.c

INCLUDES_NAME = forty_two_sh.h

SRC_DIR = ./srcs/
INCLUDES_DIR = ./includes/
OBJ_DIR = ./objs/
FT_PRINTF_DIR = ./ft_printf

SRC = $(addprefix $(SRC_DIR), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_DIR), $(SRC_NAME:.c=.o))

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
#DEV_FLAGS = -fsanitize=address -fno-omit-frame-pointer
IFLAGS = -I$(FT_PRINTF_DIR)/includes -I./$(INCLUDES_DIR)
LFLAGS = -L$(FT_PRINTF_DIR) -lftprintf

CFLAGS += $(DEV_FLAGS)
LIBFTPRINTF = $(addprefix $(FT_PRINTF_DIR),"/libftprintf.a")

MAKEFILE_STATUS = $(addprefix $(addprefix $(FT_PRINTF_DIR),"/libft"),"/.makefile_status")

UNAME_S := $(shell uname -s)

define ui_line
	$(MAKEFILE_STATUS) $(1) $(2) || true
endef

all : $(NAME)

$(NAME) : $(LIBFTPRINTF) $(OBJ)
ifeq ($(UNAME_S),Linux)
	@$(CC) $(CFLAGS) $(LFLAGS) $(OBJ) $(LIBFTPRINTF) -o $(NAME)
endif
ifeq ($(UNAME_S),Darwin)
	@$(CC) $(CFLAGS) $(LFLAGS) $(OBJ) -o $(NAME)
endif

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(addprefix $(INCLUDES_DIR), $(INCLUDES_NAME))
	@mkdir -p $(OBJ_DIR)
	@gcc $(CFLAGS) -c $(IFLAGS) $< -o $@ && $(call ui_line, $@, $(NAME))

$(FT_PRINTF_DIR):
	git clone https://github.com/jjaniec/ft_printf $(FT_PRINTF_DIR) || true

$(LIBFTPRINTF): $(FT_PRINTF_DIR)
	@make -C $(FT_PRINTF_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(FT_PRINTF_DIR)

fclean: clean
	@make fclean -C $(FT_PRINTF_DIR)
	@rm -f $(NAME)

re: fclean all

tests: $(NAME)
	@echo "Todo"

.PHONY: fclean re tests all