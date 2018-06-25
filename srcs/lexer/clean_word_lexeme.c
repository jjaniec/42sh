/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_word_lexeme.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 15:18:07 by jjaniec           #+#    #+#             */
/*   Updated: 2018/06/25 14:20:14 by jjaniec          ###   ########.fr       */
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

static int		is_quote_removable(char **s, int *i, char **jump_ptr)
{
	char	*tmp;

	tmp = NULL;
	if ((tmp = has_matching_quote((*s), *i)))
	{
		if (jump_ptr)
			*jump_ptr = tmp;
		log_debug("Found removable quote @ tmp : |%s|", tmp);
		return (1);
	}
	return (0);
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
		if (s[i] == '\\')
		{
			new_data[j++] = s[i + 1];
			i += 2;
		}
		else if (((s)[i] == '\'' || (s)[i] == '"') && \
			is_quote_removable(&s, &i, &jump_ptr))
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
			}
			else
				new_data[j++] = s[++i];
			if (s[i])
				i++;
		}
		else
			new_data[j++] = s[i++];
	new_data[j] = '\0';
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
	//log_trace("Make new str");
	//new_data = get_new_data_str(*data);
	new_data = malloc(ft_strlen(*data) * sizeof(char) + 1); // faster & simpler than calculating new string size
	log_trace("Filling new str");
	fill_new_data_str(*data, new_data);
	free(*data);
	*data = new_data;
	log_debug("Replaced old data w/ |%s|", *data);
}
