/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xstrnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 18:01:35 by cyfermie          #+#    #+#             */
/*   Updated: 2018/10/16 18:03:05 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft.h"

char	*ft_xstrnew(size_t size)
{
	char	*s;

	s = ft_strnew(size);
	if (s == NULL)
	{
		ft_putstr_fd("Memory allocation error, Exit\n", 2);
		exit(1);
	}
	return (s);
}
