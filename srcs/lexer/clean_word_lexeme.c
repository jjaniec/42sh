/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_word_lexeme.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 15:18:07 by jjaniec           #+#    #+#             */
/*   Updated: 2018/06/21 19:45:18 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Returns 1 if *s character should be removed or not
** $s: data string
** $i: pos in string
** $jump_ptr: set to ptr to position of corresponding quote if passed argument
**            != NULL
*/

static int		is_removable(char **s, int *i, char **jump_ptr)
{
	char	*tmp;

	tmp = NULL;
	if (((*s)[*i] == '\\' && (*i > 0 && (*s)[*i - 1] != '\\')) || \
		(((*s)[*i] == '\'' || (*s)[*i] == '"') && \
		(tmp = has_matching_quote((*s) + *i, *i))))
	{
		if (jump_ptr && tmp)
			*jump_ptr = tmp;
		log_debug("Found removable char @ |%s|", tmp);
		return (1);
	}
	return (0);
}

/*
** Counts characters to remove count and creates new data string
*/

static char		*get_new_data_str(char *s)
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
** Fills new created data string
** $s: old data string
** $new_data: ptr to new data string
*/

static void		fill_new_data_str(char *s, char *new_data)
{
	int		i;
	int		j;
	char	*jump_ptr;

	j = 0;
	i = 0;
	jump_ptr = s;
	while (s[i])
		if (is_removable(&s, &i, &jump_ptr))
		{
			if (jump_ptr)
			{
				i++;
				while (s[i] && (s + i) != jump_ptr)
				{
					if (s[i] == '\\')
						i++;
					new_data[j++] = s[i++];
				}
				if (!s[i])
					break ;
			}
			else
			{
				log_warn("Code rouge: |%s| %d", s + i, i);
				new_data[j++] = s[++i];
			}
			i++;
		}
		else
			new_data[j++] = s[i++];
}

/*
** Removes ' and " characters from given string by calculating
** count of characters to remove, creating a new string and filling it
** without escaping characters '\' and quotes pairs
*/

void			clean_word_lexeme(char **data)
{
	char	*new_data;

	log_debug("Cleaning |%s|", *data);
	log_trace("Make new str");
	new_data = get_new_data_str(*data);
	log_trace("Filling new str");
	fill_new_data_str(*data, new_data);
	free(*data);
	*data = new_data;
	log_debug("Replaced old data w/ |%s|", *data);
}
