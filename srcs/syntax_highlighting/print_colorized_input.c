/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_colorized_input.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 17:38:26 by jjaniec           #+#    #+#             */
/*   Updated: 2018/08/22 22:43:42 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Return a pointer to next element beginning
*/

static char		*get_next_elem_begin(char *ptr)
{
	int		i;

	i = 0;
	while (is_separator(ptr[i]) && ptr[i])
		i++;
	return (ptr + i); 
}

/*
** Return a pointer to next #IFS separator (end of element)
*/

static char		*get_next_elem_end(char *ptr)
{
	int			i;

	i = 0;
	while (!(is_separator(ptr[i])) && ptr[i])
		i++;
	return (&(ptr[i]));
}

/*
** Print color associated w/ type of element found in string
*/

static void		print_prog_name_arg(struct stat *elem_stats, int elem_found, int item_nb)
{
	if (elem_found)
	{
		if (item_nb == 0)
			ft_putstr(COL_PROG_NAME_FOUND);
		else
		{
			if (S_ISDIR(elem_stats->st_mode))
				ft_putstr(COL_PROG_ARG_DIR);
			else
				ft_putstr(COL_PROG_ARG_FILE);
		}
	}
	else
	{
		if (item_nb == 0)
			ft_putstr(COL_PROG_NAME_NOT_FOUND);
		else
			ft_putstr(COL_PROG_ARG_NOT_FOUND);
	}
}

static void		print_elem_color(char *elem_ptr, char *elem_end_ptr, char **env, int *item_nb)
{
	char			c;
	struct stat		elem_stats;

	if (*elem_ptr == ';' || *elem_ptr == '&' || *elem_ptr == '|')
	{
		ft_putstr(COL_OPERATORS);
		*item_nb = -1;
	}
	else if (*elem_ptr == '-')
		ft_putstr(COL_PROG_OPT);
	else if (*elem_ptr == '\'' || *elem_ptr == '"')
		ft_putstr(COL_QUOTED_ARG);
	else
	{
		c = *elem_end_ptr;
		*elem_end_ptr = '\0';
		print_prog_name_arg(&elem_stats, elem_path_found(&elem_stats, elem_ptr, env), *item_nb);
		*elem_end_ptr = c;
	}
}

static void		print_next_elem(char *input_str, char **env, int *item_nb)
{
	char	*elem_begin_ptr;
	char	*elem_end_ptr;

	if (!(input_str && *input_str))
		return ;
	if (!(*(elem_begin_ptr = get_next_elem_begin(input_str))))
		return ;
	elem_end_ptr = get_next_elem_end(elem_begin_ptr);
	print_elem_color(elem_begin_ptr, elem_end_ptr, env, item_nb);
	write(1, input_str, (elem_end_ptr - input_str));
	ft_putstr(COL_DEFAULT);
	*item_nb += 1;
	print_next_elem(elem_end_ptr, env, item_nb);
}


void		print_colorized_input(char *input_str, char **env)
{
	int		item_nb;

	item_nb = 0;
	print_next_elem(input_str, env, &item_nb);
}