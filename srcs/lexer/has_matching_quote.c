/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_matching_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 15:20:15 by jjaniec           #+#    #+#             */
/*   Updated: 2018/07/01 12:38:04 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** When a quote is found, this function will returns the position of the corresponding
** quote in our string $s, if no corresponding quotes are found, return NULL
** to print an "unmatched quote" error and exit
*/

char		*has_matching_quote(char *s, int pos)
{
	int		i;
	char	quote;

	i = pos + 1;
	quote = *(s + pos);
	//log_debug("Searching %c in |%s| - pos %d - len %d", quote, s + i, i, ft_strlen(s));
	while (s[i])
	{
		if (s[i] == quote)
		{
			//log_debug("return |%s|", s + i);
			return (s + i);
		}
		else if (s[i] == '\\')
			handle_backslash_escape(s, &i, \
				(quote == '"') ? (IN_DQUOTES) : (IN_SQUOTES));
		if (s[i])
			i++;
	}
	return (NULL);
}
