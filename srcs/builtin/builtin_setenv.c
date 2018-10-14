/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 19:34:40 by jjaniec           #+#    #+#             */
/*   Updated: 2018/10/09 21:07:12 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Check args format and return 1 to print error messages if any of them is invalid
*/

static int	check_args(char **argv)
{
	char	*assign_ptr;

	while (argv && *argv)
		if (!(assign_ptr = ft_strchr(*argv, '=')))
			return (1);
		else if (is_identifier_invalid(*argv, assign_ptr))
			return (2);
		else argv++;
	return (0);
}

/*
** Print invalid parameters error message
*/

static void	print_setenv_error(int err)
{
	if (err == 1)
		ft_putstr_fd(BUILTIN_SETENV_USAGE, 2);
	else if (err == 2)
		ft_putstr_fd(SH_NAME": invalid identifiers\n", 2);
}

/*
** Add environnement variables in our t_env_entry linked list w/ add_var
*/

void		builtin_setenv(char **argv, t_environ *env, t_exec *exe)
{
	char		**ptr;
	int			err;

	(void)argv;
	(void)env;
	(void)exe;
	ptr = argv + 1;
	if (!(argv[1]))
	{
		builtin_env((char *[2]){"env", NULL}, env, exe);
		return ;
	}
	if ((err = check_args(ptr)))
	{
		print_setenv_error(err);
		exe->ret = 1;
		return ;
	}
	while (ptr && *ptr)
	{
		if (!(env->get_var(env, *ptr)))
			env->add_var(env, *ptr, NULL);
		else
			ft_strncpy(env->last_used_elem->entry, *ptr, MAX_ENV_ENTRY_LEN);
		ptr++;
	}
	exe->ret = 0;
}
