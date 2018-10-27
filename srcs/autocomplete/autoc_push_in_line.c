/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autoc_push_in_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 17:02:20 by cgaspart          #+#    #+#             */
/*   Updated: 2018/10/19 17:05:11 by cyfermie         ###   ########.fr       */
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
		if (str[i] == ' ' || str[i] == '\n' || str[i] == '$' ||
		str[i] == '\t' || str[i] == '\\' || str[i] == ';' ||
		str[i] == '&' || str[i] == '|' || str[i] == '>' ||
		str[i] == '<' || str[i] == '"' || str[i] == '\'')
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
	res = ft_xmalloc(sizeof(char) * (ft_strlen(str) + malloc_len(str)));
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\n' || str[i] == '$' ||
		str[i] == '\t' || str[i] == '\\' || str[i] == ';' ||
		str[i] == '&' || str[i] == '|' || str[i] == '>' ||
		str[i] == '<' || str[i] == '"' || str[i] == '\'')
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

static char		*get_final_line_s(struct s_line *le, char *res, char *search)
{
	char	*tmp;
	int		i;
	int		check;

	i = 0;
	check = 0;
	if (res[0] == '\\')
		check++;
	while (res[i + check])
	{
		if (res[i + check] != search[i])
		{
			tmp = ft_xstrjoin(le->cmd, &res[i + check]);
			free(res);
			return (tmp);
		}
		i++;
	}
	return (NULL);
}

static char		*get_final_line(struct s_line *le, char *str, char *search)
{
	char	*res;
	char	*tmp;

	res = add_backslash(str);
	if (!search)
	{
		tmp = ft_xstrjoin(le->cmd, res);
		free(res);
		return (tmp);
	}
	return (get_final_line_s(le, res, search));
}

void			autoc_push_in_line(struct s_line *le, char *str, char *search)
{
	char	*final_line;
	int		i;

	i = 0;
	final_line = get_final_line(le, str, search);
	if (final_line == NULL)
		return ;
	if (le->le_state.opt_colosyn)
		refresh_colosyn(le, final_line);
	else
	{
		actionk_delete_current_input(le);
		while (final_line[i])
		{
			print_key_at_end(le, final_line[i]);
			i++;
		}
	}
	free(final_line);
}
