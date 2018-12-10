/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_new_data_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 16:57:00 by cyfermie          #+#    #+#             */
/*   Updated: 2018/12/10 17:04:37 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Fills new created data string
** $s: old data string
** $new_data: ptr to new data string
*/

static int		init_vars(char **ptr, char *raw_lexeme_data,
				char ***raw_lexeme_read_ptr, char **jump_ptr)
{
	*ptr = raw_lexeme_data;
	*raw_lexeme_read_ptr = ptr;
	*jump_ptr = *ptr;
	return (NOT_IN_QUOTES);
}

static void		gros_while(struct s_fill_new_data_str_func *s,
				t_lexeme_clean_data **l, t_shell_vars *vars)
{
	while (*(s->ptr) && s->ptr != s->jump_ptr)
	{
		if (s->in_quote_type == IN_DQUOTES &&
		is_expansion_char(*l, s->in_quote_type, &s->expansion_handler))
		{
			(*(void (*)(t_lexeme_clean_data *, t_shell_vars *)) \
			(s->expansion_handler)) (*l, vars);
			continue ;
		}
		else if (*(s->ptr) == '\\')
			s->ptr += 1 * handle_escape_offset(s->ptr, s->in_quote_type);
		(*((*l)->clean_data_write_ptr++)) = *(s->ptr++);
		(*((*l)->clean_data_write_ptr)) = '\0';
	}
}

void			fill_new_data_str(t_lexeme_clean_data *l, t_shell_vars *vars)
{
	struct s_fill_new_data_str_func s;

	s.in_quote_type = init_vars(&s.ptr, l->raw_lexeme_data, \
	&(l->raw_lexeme_read_ptr), &s.jump_ptr);
	while (s.ptr && *(s.ptr))
	{
		if (is_expansion_char(l, s.in_quote_type, &s.expansion_handler))
			(*(void (*)(t_lexeme_clean_data *, t_shell_vars *)) \
			(s.expansion_handler)) (l, vars);
		else if (*(s.ptr) == '\\' && (*(s.ptr += sizeof(char) *
		handle_escape_offset(s.ptr, NOT_IN_QUOTES))))
			(*(l->clean_data_write_ptr++)) = *(s.ptr++);
		else if ((*(s.ptr) == '\'' || *(s.ptr) == '"') &&
		is_quote_removable(s.ptr, &s.jump_ptr, &s.in_quote_type) && (++s.ptr))
		{
			gros_while(&s, &l, vars);
			if (*(s.ptr))
				s.ptr++;
		}
		else
			(*(l->clean_data_write_ptr++)) = *(s.ptr++);
	}
	*(l->clean_data_write_ptr) = '\0';
}
