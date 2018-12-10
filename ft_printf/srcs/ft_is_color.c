/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 22:49:56 by jjaniec           #+#    #+#             */
/*   Updated: 2018/02/14 18:46:10 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Parse prefixes "(F/B)G" if present and return an id of the prefix,
** if not found, return -1 and print string
*/

static int	ft_parse_prefixes(char *cl)
{
	if (!((cl[0] == 'F' || cl[0] == 'B') && \
		cl[1] == 'G' && cl[2] == '_'))
		return (-1);
	else
		return ((cl[0] == 'F') ? (1) : (2));
}

/*
** Parse prefix of color "LIGHT" or "DARK"
*/

static int	ft_parse_cl_attribute(char *cl)
{
	if (ft_strncmp(cl, "LIGHT_", 6) == 0)
		return (2);
	if (ft_strncmp(cl, "DARK_", 5) == 0)
		return (1);
	return (0);
}

/*
** Return 1 if $cl is a defined color, otherwise return 0
*/

int			*ft_is_color(char *cl)
{
	int		attr_id;
	int		prefx_id;
	int		*ret;

	if ((prefx_id = ft_parse_prefixes(cl)) == -1)
		return (NULL);
	attr_id = ft_parse_cl_attribute(cl + ((prefx_id != 0) ? (3) : (0)));
	ret = malloc(sizeof(int) * 2);
	ret[0] = prefx_id;
	ret[1] = attr_id;
	return (ret);
}
