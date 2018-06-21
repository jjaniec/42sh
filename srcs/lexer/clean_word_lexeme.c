/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_word_lexeme.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 15:18:07 by jjaniec           #+#    #+#             */
/*   Updated: 2018/06/21 17:41:39 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Returns 1 if *s character should be removed or not
*/

static int	is_removable(char **s, int *i, char **jump_ptr)
{
	char	*tmp;

	tmp = NULL;
	if (((*s)[*i] == '\\' && (*i > 0 && (*s)[*i - 1] != '\\')) || \
		(((*s)[*i] == '\'' || (*s)[*i] == '"') && \
		(tmp = has_matching_quote((*s) + *i, *i))))
	{
		if (jump_ptr && tmp)
			*jump_ptr = tmp;
		return (1);
	}
	return (0);
}

/*
** Counts characters to remove count and creates new string
*/

static char	*get_new_data_str(char *s)
{
	int		i;
	int		quotes_to_remove_count;
	char	*new_data_str;
	int		new_data_str_size;
	char	*jump_ptr;
	int		s_len;

	s_len = ft_strlen(s);
	i = 0;
	quotes_to_remove_count = 0;
	while (s[i])
		if (is_removable(&s, &i, &jump_ptr))
		{
			quotes_to_remove_count += (s[i] == '"' || s[i] == '\'') ? (2) : (1);
			s = jump_ptr + sizeof(char);
			i = 0;
		}
		else
			i += 1;
	new_data_str_size = (sizeof(char) * ((s_len - quotes_to_remove_count) + 1));
	new_data_str = malloc(new_data_str_size);
	new_data_str[new_data_str_size - 1] = '\0';
	return (new_data_str);
}

/*
** Removes ' and " characters from given string
*/

void		clean_word_lexeme(char **data)
{
	int		i;
	int		j; // Used for counting quotes count to remove in old *data and rewrite new string
	char	*new_data;
	char	c;

	log_debug("Cleaning |%s|", *data);
	new_data = get_new_data_str(*data);
	i = -1;
	j = 0;
	while ((*data)[++i])
		if (((*data)[i] == '\'' || (*data)[i] == '"') && has_matching_quote(*data + i, i))
		{
			c = (*data)[i++];
			while ((*data)[i] != c)
				new_data[j++] = (*data)[i++];
		}
		else if ((*data)[i] != '\\')
			new_data[j++] = (*data)[i];
	free(*data);
	*data = new_data;
	log_debug("Replaced old data w/ |%s|", *data);
}
