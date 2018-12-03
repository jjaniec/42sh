/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 19:40:20 by jjaniec           #+#    #+#             */
/*   Updated: 2018/12/03 19:33:17 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

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

static int	print_env_content(char **environ)
{
	while (environ && *environ)
	{
		ft_putstr(*environ++);
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}

static char	**handle_parameters(char **argv, t_environ *env_struct, \
				t_environ **env_struct_to_use, char ***tmp_environ_start)
{
	if (!(argv && *argv))
		return (NULL);
	argv = parse_options(NULL, argv, g_env_opts, NULL);
	if (is_option_activated("i", g_env_opts, NULL))
		init_environ_struct_ptrs(\
			(*env_struct_to_use = ft_xmalloc(sizeof(t_environ))));
	else
		(*env_struct_to_use) = env_struct;
	*tmp_environ_start = \
		&((*env_struct_to_use)->environ[(*env_struct_to_use)->entry_count]);
	while (*argv && ft_strchr(*argv, '='))
	{
		if (!((*env_struct_to_use)->entry_count < MAX_ENV_ENTRIES))
			break ;
		if ((*env_struct_to_use)->get_var((*env_struct_to_use), *argv))
			ft_strncpy((*env_struct_to_use)->last_used_elem->entry, *argv, \
				MAX_ENV_ENTRY_LEN);
		else
			(*env_struct_to_use)->add_var((*env_struct_to_use), *argv, NULL);
		argv += 1;
	}
	(*env_struct_to_use)->environ[(*env_struct_to_use)->entry_count] = NULL;
	(g_env_opts[1]).opt_status = false;
	return (argv);
}

int			exec_command_passed_in_last_parameters(char **command_begin_ptr, \
				char **child_env)
{
	char	*prog_path;
	pid_t	child_pid;
	int		status;
	pid_t	waited_pid;

	if (!(command_begin_ptr && *command_begin_ptr && \
		(prog_path = resolve_cmd_path(*command_begin_ptr, NULL))))
		return (1);
	if ((child_pid = fork()) == -1)
		ft_putstr_fd("env: Fork returned an error\n", 2);
	else if (!child_pid)
	{
		log_debug("Start %s params: %s env %p", prog_path, \
			*command_begin_ptr, child_env);
		execve(prog_path, command_begin_ptr, child_env);
		exit(EXIT_FAILURE);
	}
	else if (child_pid)
	{
		waited_pid = waitpid(child_pid, &status, 0);
		return (get_process_return_code(&status, waited_pid, child_pid));
	}
	return (EXIT_FAILURE);
}

int			builtin_env_(char **argv, t_environ *env)
{
	t_environ		*env_struct_to_use;
	char			**command_begin_ptr;
	char			**tmp_envbegin;

	if (env)
	{
		command_begin_ptr = handle_parameters(argv, env, \
			&env_struct_to_use, &tmp_envbegin);
		if (!(command_begin_ptr && *command_begin_ptr))
			print_env_content(env_struct_to_use->environ);
		else
			exec_command_passed_in_last_parameters(command_begin_ptr, \
				(env_struct_to_use != env) ? \
				(tmp_envbegin) : (env_struct_to_use->environ));
		if (env_struct_to_use != env)
		{
			free_env_entries(env_struct_to_use, \
				env_struct_to_use->env_entries_list);
			free(env_struct_to_use);
		}
		else
			while (*tmp_envbegin)
				env_struct_to_use->del_var(env_struct_to_use, *tmp_envbegin);
	}
	return ((env) ? (0) : (1));
}

void		builtin_env(char **argv, t_environ *env, t_exec *exe)
{
	(void)argv;
	if (argv[1])
	{
		if (exe)
			exe->ret = builtin_env_(argv, env);
		else
			builtin_env_(argv, env);
		return ;
	}
	print_env_content(env->environ);
	if (exe)
		exe->ret = 0;
}
