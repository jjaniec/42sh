/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_2d_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 20:17:27 by jjaniec           #+#    #+#             */
/*   Updated: 2018/11/30 18:08:57 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

char		**ft_dup_2d_array(char **arr)
{
	unsigned int		l;
	char				**ret;
	unsigned int		i;

	l = ft_count_elem_2d_array(arr);
	ret = ft_xmemalloc(sizeof(char *) * (l + 1));
	ret[l] = NULL;
	i = 0;
	while (l != i)
	{
		ret[i] = ft_xstrdup(arr[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
