/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 21:45:34 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/11 18:58:34 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Compare current option string $opt_str with each $opt_name
** in current option struct in $opt_list
*/

static t_option	*get_opt_elem(t_option *opt_list, char *opt_str)
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

/*
** Toggle option status if specified option was found,
** and if $char_opt_index is specified, store at
** char_opt_index[char_opt], pointer to option struct,
** it will allow us to not search through all options
** when we need to read an element in the structure, for example,
** to read description of 'h' option:
** $char_opt_index['h']->opt_desc for example
**
** If specified option was not found, print error message and exit
*/

static void		toggle_str_opt(t_option *opt_list, char *str_opt, \
					t_option **char_opt_index)
{
	t_option	*elem_ptr;

	if ((elem_ptr = get_opt_elem(opt_list, str_opt)))
	{
		log_info("Toggled %s option", str_opt);
		elem_ptr->opt_status = true;
		if (char_opt_index && *str_opt != '-' && \
			ft_isprint(*str_opt) && *str_opt < CHAR_OPT_INDEX_SIZE)
			char_opt_index[(int)*str_opt] = elem_ptr;
	}
	else
	{
		ft_putstr_fd("No such option : ", 2);
		ft_putstr_fd(str_opt, 2);
		ft_putstr_fd("\n", 2);
		exit(OPT_NOT_FOUND_ERROR);
	}
}

/*
** When a 'char' option is found,
** store current char in a char * to compare options names w/ ft_strcmp
** in get_opt_elem()
*/

static void		toggle_char_opts(t_option *opt_list, char *char_opts, \
					t_option **char_opt_index)
{
	char		*ptr;
	char		tmp[2];

	tmp[1] = '\0';
	ptr = char_opts;
	if (ptr)
		while (*ptr)
		{
			*tmp = *ptr;
			toggle_str_opt(opt_list, tmp, char_opt_index);
			ptr++;
		}
}

/*
** Cycle through each parameter in $av to until options are found,
** (beginning w/ '-' and before "--" string) and toggle option status in their
** respective t_option structure
** When all options are skipped, return pointer to end of options in $av
*/

char			**parse_options(int *ac, char **av, \
					t_option *opt_list, t_option **char_opt_index)
{
	char		**ptr;

	ptr = &av[1];
	while ((*ac)-- > 1 && **ptr == '-' && ft_strcmp(*ptr, "--"))
	{
		if ((*ptr)[1] == '-')
			toggle_str_opt(opt_list, (*ptr) + 1, char_opt_index);
		else
			toggle_char_opts(opt_list, (*ptr) + 1, char_opt_index);
		ptr = (*ac != 0) ? (&ptr[1]) : (NULL);
	}
	return (ptr);
}
