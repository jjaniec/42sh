/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 13:41:09 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/10 17:00:40 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "../libft/libft.h"
# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>
# include <wchar.h>
# include <locale.h>
# include <limits.h>
# include <stdint.h>

# ifndef CL_FT_PRINTF
#  define CL_FT_PRINTF
#  define FG_DEFAULT		"\e[39m"
#  define FG_BLACK		"\e[30m"
#  define FG_RED		"\e[31m"
#  define FG_GREEN		"\e[32m"
#  define FG_YELLOW		"\e[33m"
#  define FG_BLUE		"\e[34m"
#  define FG_MAGENTA		"\e[35m"
#  define FG_CYAN		"\e[36m"
#  define FG_LIGHT_GREY		"\e[37m"
#  define FG_DARK_GREY		"\e[90m"
#  define FG_LIGHT_RED		"\e[91m"
#  define FG_LIGHT_GREEN	"\e[92m"
#  define FG_LIGHT_YELLOW	"\e[93m"
#  define FG_LIGHT_BLUE		"\e[94m"
#  define FG_LIGHT_MAGENTA	"\e[95m"
#  define FG_LIGHT_CYAN		"\e[96m"
#  define FG_WHITE		"\e[97m"

#  define BG_DEFAULT		"\e[49m"
#  define BG_BLACK		"\e[40m"
#  define BG_RED		"\e[41m"
#  define BG_GREEN		"\e[42m"
#  define BG_YELLOW		"\e[43m"
#  define BG_BLUE		"\e[44m"
#  define BG_MAGENTA		"\e[45m"
#  define BG_CYAN		"\e[46m"
#  define BG_LIGHT_GREY		"\e[47m"
#  define BG_DARK_GREY		"\e[100m"
#  define BG_LIGHT_RED		"\e[101m"
#  define BG_LIGHT_GREEN	"\e[102m"
#  define BG_LIGHT_YELLOW	"\e[103m"
#  define BG_LIGHT_BLUE		"\e[104m"
#  define BG_LIGHT_MAGENTA	"\e[105m"
#  define BG_LIGHT_CYAN		"\e[106m"
#  define BG_WHITE		"\e[107m"
# endif

typedef struct	s_arg
{
	char			*data_converted;
	char			*flag;
	char			*modifiers;
	char			*width;
	char			*precision;
	char			*attributes;
	struct s_arg	*next;
}				t_arg;

int				ft_printf(const char *format, ...);

int				ft_count_args(const char *format);

t_arg			*ft_create_arglist(va_list va_ptr, const char *format);

t_arg			*ft_create_elem(va_list va_ptr, const char *format, \
	int pos);

void			ft_debug_args(const char *format, t_arg *li);

void			ft_print_next_arg(t_arg **li, const char *format, \
	int *i, int *r);

int				ft_print_color(const char *format, int *i);

int				ft_is_flag_c(char c);

int				ft_is_modifier(char c, char c2);

char			*ft_get_flag(const char *format, int pos);

char			*ft_convert_arg_no_modifiers(va_list va_arg, char flag);

char			*ft_char_to_str(char c);

void			ft_putwchar(wchar_t c);

void			ft_putwstr(wchar_t *s);

char			ft_wchar_byte_to_char(int w_char_len, int bytepos, wchar_t c);

int				ft_wchar_masklen(wint_t c);

int				ft_sizeof_wstr_to_char(wchar_t *ws);

char			*ft_wchar_tptr_to_str(wchar_t *ws);

char			*ft_wchar_t_to_str(wint_t c);

int				ft_is_flag(const char *format, int i);

int				ft_printf_no_args(const char *format);

char			*ft_parse_attributes(const char *format, int *pos);

int				ft_is_attribute(char c);

int				ft_get_attributes_len(const char *format, int pos);

char			*ft_parse_width(const char *format, int *pos);

int				ft_get_width_len(const char *format);

char			*ft_parse_precision(const char *format, int *pos);

void			ft_apply_options(t_arg **e);

void			ft_apply_attributes(t_arg **e);

void			ft_apply_attr_minus_zero(t_arg **e);

void			ft_apply_attr_plus(t_arg **e);

void			ft_apply_attr_space(t_arg **e);

char			*ft_generate_width(int l, char c);

void			ft_apply_width(t_arg **e);

void			ft_byte_swap(char *a, char *b);

void			*ft_free_elem(t_arg *e);

void			ft_putchar_printf(char c, int *r);

char			*ft_printf_str_arg(char *a);

void			ft_apply_precision(t_arg **e);

int				ft_is_conv_numeric(t_arg **e);

char			*ft_parse_modifiers(const char *format, int *pos);

char			*ft_convert_arg_modifiers(va_list va_ptr, t_arg **e);

char			*ft_imax_toa(intmax_t n);

char			*ft_voidptr_to_hex(void *data);

void			ft_apply_attr_hashtag(t_arg **e);

int				ft_atoi_hex(char *s);

char			*ft_strnotchr(const char *s, char c);

char			*ft_uitoa_base(uintmax_t n, uint8_t b);

void			ft_printf_percent(const char *format, int *pos, \
	int *r);

char			*ft_convert_arg_mod_l(va_list va_ptr, char c);

char			*ft_convert_arg_mod_l(va_list va_ptr, char c);

char			*ft_convert_arg_mod_h(va_list va_ptr, char c);

char			*ft_convert_arg_mod_ll(va_list va_ptr, char c);

char			*ft_convert_arg_mod_hh(va_list va_ptr, char c);

char			*ft_convert_arg_mod_j(va_list va_ptr, char c);

char			*ft_convert_arg_mod_z(va_list va_ptr, char c);

void			*ft_free_arglist(t_arg *l, va_list va_ptr);

int				ft_print_until_validconv(const char *format, int i, \
	t_arg *args);

int				*ft_is_color(char *cl);

void			ft_print_color_id(char *cl, int *tab_);

#endif
