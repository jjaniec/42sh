/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_matching_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 15:20:15 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/20 15:46:03 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** When a quote is found, this function will returns the position of the
** corresponding quote in our string $s, if no corresponding quotes are found,
** return NULL
** to print an "unmatched quote" error and exit
*/

char		*has_matching_quote(char *s, char quote)
{
	char	*ptr;

	ptr = s + 1;
	while (ptr && *ptr)
	{
		if (*ptr == quote)
			return (ptr);
		else if (*ptr == '\\')
			ptr += sizeof(char) * handle_escape_offset(ptr, \
				(quote == '"') ? (IN_DQUOTES) : (IN_SQUOTES));
		if (*ptr)
			ptr++;
	}
	return (NULL);
}
