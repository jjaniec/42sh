/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_ptr_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 20:31:40 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/19 20:35:50 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
** Frees a list of pointers and set all to NULL
*/

void		ft_free_ptr_list(int count, ...)
{
	va_list		va_ptr;
	void		**ptr;

	va_start(va_ptr, count);
	while (count > 0)
	{
		ptr = va_arg(va_ptr, void **);
		free(*ptr);
		(*ptr) = NULL;
		count -= 1;
	}
	va_end(va_ptr);
}
