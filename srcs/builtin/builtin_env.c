/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 19:40:20 by jjaniec           #+#    #+#             */
/*   Updated: 2018/12/10 19:35:58 by sbrucker         ###   ########.fr       */
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

/*
** Print passed environnement content
*/

static int	print_env_content(char **environ)
{
	while (environ && *environ)
	{
		ft_putstr(*environ++);
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}

/*
** Prepare temporary environnement, depending on options,
** and assing new environnement vars passed as parameters
*/

static char	**handle_parameters(char **argv, t_environ *env_struct, \
				t_environ **env_struct_to_use)
{
	if (!(argv && *argv))
		return (NULL);
	argv = parse_options(NULL, argv, g_env_opts, NULL);
	*env_struct_to_use = ft_xmalloc(sizeof(t_environ));
	if (!is_option_activated("i", g_env_opts, NULL))
		init_environ(env_struct->environ, *env_struct_to_use);
	else
		init_environ_struct_ptrs(*env_struct_to_use);
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
	return (argv);
}

/*
** Resolve command path, fork, and wait/exec program
*/

static int	exec_command_passed_in_last_parameters(char **command_begin_ptr, \
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
		fatal_fork_fail();
	else if (!child_pid)
	{
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

/*
** exec command passed in last parameters or just print temporary environnement
** when no commands are specified
*/

static int	builtin_env_(char **argv, t_environ *env)
{
	int				r;

	r = 0;
	if (!(argv && *argv))
		print_env_content(env->environ);
	else
		r = exec_command_passed_in_last_parameters(\
			argv, env->environ);
	return (r);
}

/*
** Prepare temporary environnement and pass it to builtin_env
** or just print current environnement if no arguments are passed
*/

void		builtin_env(char **argv, t_environ *env, t_exec *exe)
{
	t_environ	*temp_env;
	char		**command_begin_ptr;

	temp_env = NULL;
	if (argv[1] && \
		(command_begin_ptr = handle_parameters(argv, env, &temp_env)))
	{
		if (exe)
			exe->ret = builtin_env_(command_begin_ptr, temp_env);
		else
			builtin_env_(command_begin_ptr, temp_env);
		(g_env_opts[1]).opt_status = false;
	}
	else
	{
		if (exe)
			exe->ret = 0;
		print_env_content(env->environ);
	}
	if (temp_env)
	{
		free_env_entries(temp_env, \
			temp_env->env_entries_list);
		free(temp_env);
	}
}
