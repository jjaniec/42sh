/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_colorized_input.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 17:38:26 by jjaniec           #+#    #+#             */
/*   Updated: 2018/08/29 16:03:50 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Return a pointer to next element begin
*/

static char		*get_next_elem_begin(char *input_str, t_lexeme *lexeme)
{
	char	*ret;

	(void)lexeme;
	ret = input_str;
	while (ft_strrchr(IFS, *ret))
		ret++;
//	log_debug("Colorization elem_begin: |%s|", ret);
	return (ret);
}

/*
** Return a pointer to next element end
*/

static char		*get_next_elem_end_quotes(char *elem_begin, t_lexeme *lexeme)
{
	char	*ptr;

	(void)lexeme;
	ptr = elem_begin;
	ptr++;
	while (*ptr && *elem_begin != *ptr)
		ptr++;
	if (*ptr == *elem_begin)
		ptr++;
//	log_debug("Colorization elem_end_quotes: |%s|", ptr);
	return (ptr);
}

static char		*get_next_elem_end(char *elem_begin, t_lexeme *lexeme)
{
	char	*ptr;

	(void)lexeme;
	if (lexeme->type == T_REDIR_OPT || lexeme->type == T_CTRL_OPT)
		ptr = (elem_begin + ft_strlen((char *)((*lexeme).data)));
	else
	{
		ptr = elem_begin;
		if (*elem_begin == '\'' || *elem_begin == '"')
			return (get_next_elem_end_quotes(elem_begin, lexeme));
		while (*ptr && !(ft_strchr(IFS, *ptr)))
			ptr++;
	}
//	log_debug("Colorization elem_end: |%s|", ptr);
	return (ptr);
}

static void		get_lexeme_substring(char *input_str, t_lexeme *lexeme, \
					char **lexeme_str_begin, char ** lexeme_str_end)
{
	*lexeme_str_begin = get_next_elem_begin(input_str, lexeme);
	if (!(*lexeme_str_begin))
	{
		*lexeme_str_begin = NULL;
		return ;
	}
	*lexeme_str_end = get_next_elem_end(*lexeme_str_begin, lexeme);
}

void		print_colorized_input(char *input_str, char **env, t_lexeme *lexemes)
{
	t_lexeme	*cur_lexeme;
	char		*lexeme_str_begin;
	char		*lexeme_str_end;
	char		*ptr;

	cur_lexeme = lexemes;
	ptr = input_str;
	while (ptr && cur_lexeme && *ptr)
	{
		get_lexeme_substring(ptr, cur_lexeme, &lexeme_str_begin, &lexeme_str_end);
		if (!(lexeme_str_begin))
			break ;
		print_lexeme_colorized(lexeme_str_begin, lexeme_str_end, ptr, cur_lexeme, env);
		cur_lexeme = cur_lexeme->next;
		ptr = lexeme_str_end;
	}
	ft_putchar('\n');
}