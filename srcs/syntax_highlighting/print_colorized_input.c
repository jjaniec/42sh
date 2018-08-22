/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_colorized_input.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 17:38:26 by jjaniec           #+#    #+#             */
/*   Updated: 2018/08/22 20:42:41 by jjaniec          ###   ########.fr       */
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

static int		print_elem_color(char *elem_ptr)
{
	/*if (*elem_ptr == ';' || *elem_ptr == '&' || *elem_ptr == '|')
		*item_nb = -1;
	# define COL_PROG_NAME_NOT_FOUND "\e[1;31m"
	# define COL_PROG_NAME_FOUND "\e[1;32m"
	*/
	if (*elem_ptr == '-')
		ft_putstr(COL_PROG_OPT);
	else if (*elem_ptr == '\'' || *elem_ptr == '"')
		ft_putstr(COL_QUOTED_ARG);
	else
		return (0);
	return (1);
}

static void		print_next_elem(char *input_str)
{
	char	*elem_begin_ptr;
	char	*elem_end_ptr;

	if (!(input_str && *input_str))
		return ;
	if (!(*(elem_begin_ptr = get_next_elem_begin(input_str))))
		return ;
	elem_end_ptr = get_next_elem_end(elem_begin_ptr);
	print_elem_color(elem_begin_ptr);
	write(1, input_str, (elem_end_ptr - input_str));
	ft_putstr(COL_DEFAULT);
	print_next_elem(elem_end_ptr);
}


void		print_colorized_input(char *input_str)
{
	print_next_elem(input_str);
}