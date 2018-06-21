/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_matching_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 15:20:15 by jjaniec           #+#    #+#             */
/*   Updated: 2018/06/21 15:21:48 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

char		*has_matching_quote(char *s, int pos)
{
	char	*next_quote;
	char	quote;
	char	*ptr;

	ptr = s;
	quote = *ptr;
	next_quote = NULL;
	log_debug("Searching %c in |%s| - pos %d - len %d", quote, ptr + sizeof(char), pos, ft_strlen(s));
	while (ptr && *ptr && (next_quote = (ft_strchr(ptr + sizeof(char), quote))))
	{
		if ((*(next_quote - sizeof(char)) != '\\') || (*(next_quote - (sizeof(char) * 2)) == '\\'))
		{
			log_debug("return |%s|", next_quote);
			return (next_quote);
		}
		ptr = next_quote;
		log_debug("Searching %c in |%s| + 1 - pos %d - len %d", quote, ptr, pos, ft_strlen(s));
	}
	log_debug("No matching quote found");
	return (NULL);
}
