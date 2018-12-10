/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_content.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 15:16:18 by jjaniec           #+#    #+#             */
/*   Updated: 2018/10/16 17:45:24 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
** Append to ft_read_content's buffer, following of file descriptor, with a
** size of ($BUFF_SIZE * $bufsize_multiplier) bytes
*/

static char	*ft_resize_buf(int fd, char *buf, int *bufsize_multiplier,
							int *wrote)
{
	char	*buf2;

	buf2 = malloc(42 * (*bufsize_multiplier) + 1);
	*wrote = read(fd, buf2, 42 * (*bufsize_multiplier));
	buf2[*wrote] = '\0';
	*bufsize_multiplier = *bufsize_multiplier + 1;
	return (ft_strjoin_free(buf, buf2));
}

/*
** Read the first $BUFF_SIZE bytes of file descriptor passed in parameter
** and store it in a malloc'ed char *
*/

char		*ft_read_content(int fd)
{
	char	*buf;
	int		x;
	int		multiplier;

	multiplier = 1;
	buf = malloc(42 + 1);
	x = read(fd, buf, 42);
	buf[x] = '\0';
	if (x < 42)
		return (buf);
	while (x > 0)
		buf = ft_resize_buf(fd, buf, &multiplier, &x);
	return (buf);
}
