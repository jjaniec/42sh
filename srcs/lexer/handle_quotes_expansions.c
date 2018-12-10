/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes_expansions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 15:18:07 by jjaniec           #+#    #+#             */
/*   Updated: 2018/12/10 17:07:29 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Returns 1 if *s character should be removed or not
** $s: data string
** $i: pos in string
** $jump_ptr: set to ptr to position of corresponding quote if passed argument
**            != NULL
*/

int				is_quote_removable(char *s, char **jump_ptr,
				int *quote_type)
{
	char	*tmp;
	char	c;
	char	*ptr;

	tmp = NULL;
	ptr = s;
	c = *ptr;
	if ((tmp = has_matching_quote(ptr, c)))
	{
		if (jump_ptr)
			*jump_ptr = tmp;
		log_debug("Found removable quote @ : |%s|", tmp);
		if (c == '"')
			*quote_type = IN_DQUOTES;
		else if (c == '\'')
			*quote_type = IN_SQUOTES;
		return (1);
	}
	return (0);
}

/*
** Returns 1 if c is an expansion specifier char and store handler
** in *callback,
** otherwise return 0
*/

int				is_expansion_char(t_lexeme_clean_data *l, int in_quote_type, \
					void **expansion_handler_ptr)
{
	char	*ptr;

	ptr = *(l->raw_lexeme_read_ptr);
	*expansion_handler_ptr = NULL;
	if (*ptr == '$')
		*expansion_handler_ptr = handle_dollar_expansion;
	else if (*ptr == '~' && \
		in_quote_type == NOT_IN_QUOTES && \
		(ptr == l->raw_lexeme_data || is_separator(*(ptr - 1))) && \
		(!(*(ptr + 1)) || *(ptr + 1) == '/'))
		*expansion_handler_ptr = handle_tild_expansion;
	return ((*expansion_handler_ptr) ? (1) : (0));
}

/*
** Removes ' and " characters from given string,
** creating a new string and filling it
** without escaping characters '\', quotes pairs
** and expansing '$' or '~' expansions when needed
*/

void			handle_quotes_expansions(char **data)
{
	t_lexeme_clean_data		new_lex_data;

	new_lex_data.raw_lexeme_data = *data;
	new_lex_data.clean_data_size = ft_strlen(*data) * sizeof(char) + 1;
	new_lex_data.clean_data = ft_xmalloc(new_lex_data.clean_data_size);
	ft_memset(new_lex_data.clean_data, '\0', new_lex_data.clean_data_size);
	new_lex_data.clean_data_write_ptr = new_lex_data.clean_data;
	fill_new_data_str(&new_lex_data, get_shell_vars());
	free(*data);
	*data = new_lex_data.clean_data;
	log_trace("Replaced old data w/ after quotes & \
	expansions handling |%s|", *data);
}
