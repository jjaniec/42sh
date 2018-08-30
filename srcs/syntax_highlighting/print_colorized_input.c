/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_colorized_input.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 17:38:26 by jjaniec           #+#    #+#             */
/*   Updated: 2018/08/30 19:56:30 by cyfermie         ###   ########.fr       */
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
	while (*ret && ft_strchr(IFS, *ret))
		ret++;
	if (!(*ret))
		return (NULL);
//	log_debug("Colorization elem_begin: |%s|", ret);
	return (ret);
}

/*
** Return a pointer to next element end w/ IFS separators or
** w/ get_next_elem_end_quotes() when quotes
** are found at the beginning of the element
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
	if (*ptr == '\'' || *ptr == '"')
		return (get_next_elem_end_quotes(ptr, lexeme));
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
		while (*ptr && !(ft_strchr(IFS, *ptr)) && !is_operator(*ptr))
			ptr++;
	}
//	log_debug("Colorization elem_end: |%s|", ptr);
	return (ptr);
}

/*
** Calls get_next_elem_(begin/end) functions
** to store pointers of current lexeme beginning and end in input string, in
** lexeme_str_begin and lexeme_str_end
*/

static void		get_lexeme_substring(char *input_str, t_lexeme *lexeme, \
					char **lexeme_str_begin, char **lexeme_str_end)
{
	*lexeme_str_begin = get_next_elem_begin(input_str, lexeme);
	if (!(*lexeme_str_begin))
	{
		*lexeme_str_begin = NULL;
		return ;
	}
	*lexeme_str_end = get_next_elem_end(*lexeme_str_begin, lexeme);
}

/*
** Cycle through each lexeme,
** call get_lexeme_substring to find beginning and end of lexeme in input string
** and print associated color w/ print_lexeme_colorized
*/

void		print_colorized_input(char *input_str, char **env)
{
	t_lexeme	*cur_lexeme;
	char		*lexeme_str_begin;
	char		*lexeme_str_end;
	char		*ptr;

	cur_lexeme = lexer(input_str);
	ptr = input_str;
	while (ptr && cur_lexeme && *ptr)
	{
		get_lexeme_substring(ptr, cur_lexeme, &lexeme_str_begin, \
			&lexeme_str_end);
		if (!(lexeme_str_begin))
			break ;
		print_lexeme_colorized(lexeme_str_begin, lexeme_str_end, \
			ptr, cur_lexeme, env);
		cur_lexeme = cur_lexeme->next;
		ptr = lexeme_str_end;
	}
}