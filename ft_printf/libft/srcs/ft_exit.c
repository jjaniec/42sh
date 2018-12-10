/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 21:19:36 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/19 21:20:05 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_exit(int exit_value, const char *msg)
{
	if (msg != NULL)
		write(STDERR_FILENO, msg, ft_strlen(msg));
	exit(exit_value);
}
