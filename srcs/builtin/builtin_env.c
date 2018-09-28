/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 19:40:20 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/28 20:20:43 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** https://www.unix.com/man-page/posix/1posix/env
*/

t_option		g_env_opts[] = {
	{{"h", "-help"}, "Print help and exit", false},
	{{"i"}, "Invoke utility with exactly the environment specified by the \
		arguments; the inherited environment will be ignored completely.", \
		false},
	{{NULL}, NULL, false}
};

static void		print_env_content(char **environ)
{
	while (environ && *environ)
		ft_putendl(*environ++);
}

static void	handle_parameters(char **argv, t_environ *env_struct)
{
	t_environ		*env_struct_to_use;
	char			**tmp_environ_start;
	int				starting_entry_count;

	parse_options(NULL, argv + 1, g_env_opts, NULL);
	if (is_option_activated("i", g_env_opts, NULL))
	{
		env_struct_to_use = malloc(sizeof(t_environ));
		init_environ_struct(env_struct_to_use);
	}
	else
		env_struct_to_use = env_struct;
	tmp_environ_start = \
		&(env_struct_to_use->environ[env_struct_to_use->entry_count]);
	starting_entry_count = env_struct_to_use->entry_count;
	while (argv && *argv && ft_strchr(*argv, '='))
	{
		if (!(env_struct_to_use->entry_count < MAX_ENV_ENTRIES))
			break ;
		ft_strncpy(env_struct_to_use->environ[env_struct_to_use->entry_count], \
			*argv, MAX_ENV_ENTRY_LEN);
		env_struct_to_use->entry_count += 1;
		argv += 1;
	}
	// here : exec command
	if (env_struct_to_use != env_struct)
		free(env_struct_to_use);
	else
		while (*tmp_environ_start)
			*tmp_environ_start++ = NULL;
}

int		builtin_env(char **argv, t_environ *env, t_exec *exe)
{
	(void)argv;
	(void)exe;
	if (env)
	{
		if (!(argv[1]))
		{
			print_env_content(env->environ);
			return (0);
		}
		handle_parameters(argv + 1, env);
	}
	return (1);
}
