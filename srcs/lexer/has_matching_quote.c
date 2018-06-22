/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_matching_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 15:20:15 by jjaniec           #+#    #+#             */
/*   Updated: 2018/06/22 15:39:29 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

char		*has_matching_quote(char *s, int pos)
{
	int		i;
	char	quote;

	i = pos + 1;
	quote = *(s + pos);
	log_debug("Searching %c in |%s| - pos %d - len %d", quote, s + i, i, ft_strlen(s));
	while (s[i])
	{
		if (s[i] == quote)
		{
			log_debug("return |%s|", s + i);
			return (s + i);
		}
		else if (s[i] == '\\')
		{
			log_debug("Skipping |%s|", s + i + 1);
			i += 1;
		}
		if (s[i])
			i++;
	}
	log_debug("No matching quote found");
	return (NULL);
}
