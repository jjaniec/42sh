/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 17:15:53 by jjaniec           #+#    #+#             */
/*   Updated: 2018/02/01 12:18:49 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** Multiple strchr commands in one
*/

char	*ft_strnchr(char *s, int count, ...)
{
	va_list		va_;
	int			i;

	va_start(va_, count);
	i = 0;
	while (i < count)
	{
		ft_strchr(s, va_arg(va_, int));
		i++;
	}
	va_end(va_);
	return (NULL);
}
