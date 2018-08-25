/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_colorized_input.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 17:38:26 by jjaniec           #+#    #+#             */
/*   Updated: 2018/08/25 08:40:39 by jjaniec          ###   ########.fr       */
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
	return (ret);
}

/*
** Return a pointer to next element end
*/

static char		*get_next_elem_end(char *elem_begin, t_lexeme *lexeme)
{
	return (&(elem_begin[ft_strlen(lexeme->data)]));
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