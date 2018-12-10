/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xstrdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 16:16:55 by jjaniec           #+#    #+#             */
/*   Updated: 2018/10/17 16:21:02 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft.h"

char	*ft_xstrdup(const char *s)
{
	char	*new;

	new = ft_strdup(s);
	if (new == NULL)
	{
		ft_putstr_fd("Memory allocation error, Exit\n", 2);
		exit(1);
	}
	return (new);
}
