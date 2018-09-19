/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 17:51:12 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/17 17:57:26 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memcpy(void *, const void *, size_t);

void	*ft_realloc(void *ptr, size_t original_size, size_t new_size)
{
	void	*new;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	else if (ptr == NULL)
		return (malloc(new_size));
	if ((new = malloc(new_size)) == NULL)
		return (NULL);
	if (new_size < original_size)
		ft_memcpy(new, ptr, new_size);
	else
		ft_memcpy(new, ptr, original_size);
	free(ptr);
	return (new);
}
