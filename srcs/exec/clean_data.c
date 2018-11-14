/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 16:44:40 by sbrucker          #+#    #+#             */
/*   Updated: 2018/11/11 16:45:03 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Determines if string should be passed to handle_quotes_expansions
** to remove quotes / backslashes / replace expansion specifiers
*/

static int	is_clean_needed_expansions(char **data)
{
	char	*ptr;

	ptr = EXPANSIONS_SPECIFIERS;
	while (*ptr)
		if (ft_strchr(*data, *ptr++))
			return (1);
	return (0);
}


static int	is_clean_needed(char **data)
{
	if (*data && (ft_strchr(*data, '\'') || \
			ft_strchr(*data, '"') || ft_strchr(*data, '\\') || \
			is_clean_needed_expansions(data)))
		return (1);
	return (0);
}

static void	remove_empty_data(char **data, int i)
{
	free(data[i]);
	while (data[i])
	{
		data[i] = data[i + 1];
		i++;
	}
}

void		clean_data(char **data)
{
	int		i;
	int		quoted;

	i = 0;
	while (data && data[i])
	{
		quoted = ft_strchr(data[i], '"') || ft_strchr(data[i], '`') \
		|| ft_strchr(data[i], '\'');
		if (is_clean_needed(data + i))
			handle_quotes_expansions(data + i);
		if (!data[i][0] && !quoted)
		{
			remove_empty_data(data, i);
			i--;
		}
		i++;
	}
}
