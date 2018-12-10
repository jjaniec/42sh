/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 14:40:23 by jjaniec           #+#    #+#             */
/*   Updated: 2018/02/01 12:18:43 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	ft_display_file(char *filepath)
{
	int		i;
	int		fd;
	char	buf[9999];
	int		x;

	i = -1;
	fd = open(filepath, O_RDONLY);
	x = read(fd, buf, 9999);
	if (x > 0)
	{
		buf[x] = '\0';
		while (buf[++i] != '\0')
			write(1, &buf[i], 1);
	}
	close(fd);
}
