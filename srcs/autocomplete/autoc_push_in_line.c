/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autoc_push_in_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 17:02:20 by cgaspart          #+#    #+#             */
/*   Updated: 2018/10/05 13:54:29 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

static int		malloc_len(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\n' || str[i] == '$')
			count++;
		i++;
	}
	return (count);
}

static char		*add_backslash(char *str)
{
	char	*res;
	int		j;
	int		i;

	i = 0;
	j = 0;
	res = malloc(sizeof(char) * (ft_strlen(str) + malloc_len(str)));
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\n' || str[i] == '$')
		{
			res[j] = '\\';
			j++;
		}
		res[j] = str[i];
		j++;
		i++;
	}
	res[j] = '\0';
	return (res);
}

static char		*get_final_line(struct s_line *le, char *str, char *search)
{
	char	*res;
	char	*tmp;
	int		i;
	int		check;

	i = 0;
	check = 0;
	if (!search)
		return (ft_strjoin(le->cmd, str));
	res = add_backslash(str);
	if (res[0] == '\\')
		check++;
	while (res[i + check])
	{
		if (res[i + check] != search[i])
		{
			tmp = ft_strjoin(le->cmd, &res[i + check]);
			free(res);
			return (tmp);
		}
		i++;
	}
	return (NULL);
}

void			autoc_push_in_line(struct s_line *le, char *str, char *search)
{
	char	*final_line;

	final_line = get_final_line(le, str, search);
	if (final_line == NULL)
		return ;
	refresh_colosyn(le, final_line);
	free(final_line);
}
