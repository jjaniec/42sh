/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 15:06:12 by cyfermie          #+#    #+#             */
/*   Updated: 2018/12/10 17:19:10 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static void			print_aliases(struct s_alias *alias)
{
	if (alias->key == NULL && "list is empty")
		return ;
	while (alias != NULL)
	{
		if (ft_strlen(alias->key) > 0U)
			ft_printf("'%s' = '%s'\n", alias->key, alias->value);
		alias = alias->next;
	}
}

static bool			check_option(const char *arg)
{
	if (ft_strequ(arg, "-d"))
		return (true);
	if (arg[0] == '-')
		return (false);
	while (*arg != '\0' && is_separator(*arg))
		++arg;
	if (*arg == '-')
		return (false);
	return (true);
}

/*
**	$ alias key value  => create a new entry
**	$ alias --save  => save the aliases list into a file
**	$ alias -d key  => delete an entry
**	$ alias  => display the aliases list
*/

void				builtin_alias(char **argv, t_environ *env, t_exec *exe)
{
	unsigned int	nb_args;
	struct s_alias	*alias;

	(void)env;
	exe->ret = 0;
	alias = access_alias_datas();
	nb_args = ft_count_elem_2d_array(argv + 1);
	if ((nb_args != 0 && nb_args != 1 && nb_args != 2) \
	|| (nb_args == 2 && check_option(argv[1]) == false))
	{
		ft_putstr_fd(BUILTIN_ALIAS_USAGE, STDERR_FILENO);
		exe->ret = 1;
		return ;
	}
	if (nb_args == 0)
		print_aliases(alias);
	else
		manage_aliases(argv, alias, exe, nb_args);
}
