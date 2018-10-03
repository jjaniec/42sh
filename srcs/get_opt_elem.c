/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opt_elem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 19:17:51 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/11 19:19:43 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Compare current option string $opt_str with each $opt_name
** in current option struct in $opt_list
*/

t_option	*get_opt_elem(t_option *opt_list, char *opt_str)
{
	t_option	*cur_elem;
	char		**cur_elem_identifier;
	int			i;

	cur_elem = opt_list;
	while (cur_elem && cur_elem->opt_desc)
	{
		i = 0;
		cur_elem_identifier = cur_elem->opt_name;
		while (cur_elem_identifier && *cur_elem_identifier && i < MAX_OPT_NAMES)
		{
			if (!(ft_strcmp(opt_str, *cur_elem_identifier)))
				return (cur_elem);
			cur_elem_identifier += 1;
			i++;
		}
		cur_elem += 1;
	}
	return (NULL);
}
