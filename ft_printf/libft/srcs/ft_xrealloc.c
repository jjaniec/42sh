/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xrealloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 17:52:56 by cyfermie          #+#    #+#             */
/*   Updated: 2018/10/16 17:56:23 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft.h"

void	*ft_xrealloc(void *ptr, size_t original_size, size_t new_size)
{
	void	*new;

	new = ft_realloc(ptr, original_size, new_size);
	if (new == NULL)
	{
		ft_putstr_fd("Memory allocation error, Exit\n", 2);
		exit(1);
	}
	return (new);
}
