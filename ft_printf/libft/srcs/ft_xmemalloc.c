/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xmemalloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 17:58:38 by cyfermie          #+#    #+#             */
/*   Updated: 2018/10/16 18:00:35 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft.h"

void	*ft_xmemalloc(size_t size)
{
	void	*ptr;

	ptr = ft_memalloc(size);
	if (ptr == NULL)
	{
		ft_putstr_fd("Memory allocation error, Exit\n", 2);
		exit(1);
	}
	return (ptr);
}
