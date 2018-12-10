/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_ptr_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 00:59:45 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/19 20:31:08 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
** Takes a list of pointers in paramter and sets all to NULL
*/

void		ft_init_ptr_list(int count, ...)
{
	va_list		va_ptr;
	void		*ptr;

	va_start(va_ptr, count);
	while (count > 0)
	{
		ptr = va_arg(va_ptr, void *);
		if (ptr)
			ptr = NULL;
		count -= 1;
	}
	va_end(va_ptr);
}
