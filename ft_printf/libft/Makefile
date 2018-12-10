# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/11 16:33:09 by jjaniec           #+#    #+#              #
#    Updated: 2018/11/12 16:55:11 by jjaniec          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_NAMES = ft_atoi.c \
			ft_atoll.c \
			ft_bzero.c \
			ft_count_elem_2d_array.c \
			ft_display_file.c \
			ft_div_mod.c \
			ft_exit.c \
			ft_foreach.c \
			ft_free_2d_array.c \
			ft_free_ptr_list.c \
			ft_init_ptr_list.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_itoa.c \
			ft_lstadd.c \
			ft_lstdel.c \
			ft_lstdelone.c \
			ft_lstiter.c \
			ft_lstmap.c \
			ft_lstnew.c \
			ft_memalloc.c \
			ft_memccpy.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memdel.c \
			ft_memmove.c \
			ft_memset.c \
			ft_putchar.c \
			ft_putchar_fd.c \
			ft_putendl.c \
			ft_putendl_fd.c \
			ft_putnbr.c \
			ft_putnbr_fd.c \
			ft_putstr.c \
			ft_putstr_fd.c \
			ft_range.c \
			ft_read_content.c \
			ft_realloc.c \
			ft_recursive_factorial.c \
			ft_str_capitalize.c \
			ft_str_is_positive_numeric.c \
			ft_strcat.c \
			ft_strchr.c \
			ft_strclr.c \
			ft_strcmp.c \
			ft_strcpy.c \
			ft_strdel.c \
			ft_strdup.c \
			ft_strequ.c \
			ft_strichr.c \
			ft_striter.c \
			ft_striteri.c \
			ft_strjoin.c \
			ft_strjoin_free.c \
			ft_strlcat.c \
			ft_strlen.c \
			ft_strmap.c \
			ft_strmapi.c \
			ft_strncat.c \
			ft_strnchr.c \
			ft_strncmp.c \
			ft_strncpy.c \
			ft_strnequ.c \
			ft_strnew.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strsplit.c \
			ft_strsplit_by_str.c \
			ft_strstr.c \
			ft_strsub.c \
			ft_strsub_free.c \
			ft_strtrim.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_xmalloc.c \
			ft_xmemalloc.c \
			ft_xrealloc.c \
			ft_xstrdup.c \
			ft_xstrnew.c \
			ft_xstrjoin.c \
			ft_xstrjoin_free.c

OBJS_NAMES = $(SRC_NAMES:.c=.o)
NAME = libft.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra -I. -std=c99 -Wno-pointer-arith
CFLAGS_SHARED = -Wall -Werror -Wextra -I. -shared -fPIC -std=c99 -Wno-pointer-arith
OBJ_PATH = ./objs/
SRC_PATH = ./srcs/
SRCS = $(addprefix $(SRC_PATH),$(SRC_PATH))
OBJS = $(addprefix $(OBJ_PATH),$(SRC_NAMES:.c=.o))
STATS_BAR = ./.makefile_status.sh

define ui_line
	$(STATS_BAR) $(1) $(2) || true
endef

all: $(NAME)

$(NAME):$(OBJS)
	@ar rcs $(NAME) $(OBJS)

$(OBJ_PATH)%.o : $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) -c $^ -o $@ && $(call ui_line, $@, $(NAME))

$(NAME:.a=.so): $(addprefix $(SRC_PATH),$(SRC_NAMES))
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS_SHARED) -pedantic $(addprefix $(SRC_PATH),*.c) -o libft.so

so: $(NAME:.a=.so)

clean:
	@rm -rf $(OBJ_PATH) 2> /dev/null || true

fclean: clean
	@rm -rf $(NAME) $(NAME:.a=.so) 2> /dev/null

re: fclean all

.PHONY: clean fclean all re so
