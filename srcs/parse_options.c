/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 21:45:34 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/10 22:35:08 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static t_option	*get_opt_elem(t_option *opt_list, char *opt_str)
{
	t_option	*ptr;

	ptr = opt_list;
	while (ptr && ptr->opt_name)
	{
		printf("Opt name : %s\n", ptr->opt_name);
		if (!(ft_strcmp(opt_str, ptr->opt_name)))
			return (ptr);
		ptr += 1;
	}
	return (NULL);
}

static void		toggle_str_opt(t_option *opt_list, char *str_opt)
{
	t_option	*elem_ptr;

	if ((elem_ptr = get_opt_elem(opt_list, str_opt)))
		elem_ptr->opt_status = true;
	else
	{
		ft_putstr_fd("No such option : ", 2);
		ft_putstr_fd(str_opt, 2);
		ft_putstr_fd("\n", 2);
	}
}

static void		toggle_char_opts(t_option *opt_list, char *char_opts)
{
	char		*ptr;
	char		tmp[2];

	tmp[1] = '\0';
	ptr = char_opts;
	if (ptr)
		while (*ptr)
		{
			*tmp = *ptr;
			toggle_str_opt(opt_list, tmp);
			ptr++;
		}
}

void			parse_options(int ac, char **av, t_option *opt_list)
{
	char		**ptr;

	--ac;
	ptr = &av[1];
	while (ac-- > 0 && **ptr == '-' && ft_strcmp(*ptr, "--"))
	{
		if (**ptr == '-')
		{
			if ((*ptr)[1] == '-')
				toggle_str_opt(opt_list, (*ptr) + 2);
			else
				toggle_char_opts(opt_list, (*ptr) + 1);
		}
		ptr = (ac != 0) ? (&ptr[1]) : (NULL);
	}
}
