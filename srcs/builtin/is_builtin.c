/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 16:41:20 by jjaniec           #+#    #+#             */
/*   Updated: 2018/12/10 19:13:48 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Check if function is a builtin
*/

static void	is_builtin_bis(char *cmd, void **builtin_ret_ptr)
{
	if (ft_strequ(cmd, "env"))
		*builtin_ret_ptr = &builtin_env;
	else if (ft_strequ(cmd, "exit"))
		*builtin_ret_ptr = &builtin_exit;
	else if (ft_strequ(cmd, "return"))
		*builtin_ret_ptr = &builtin_return;
	else if (ft_strequ(cmd, "history"))
		*builtin_ret_ptr = &builtin_history;
	else if (ft_strequ(cmd, "syntax"))
		*builtin_ret_ptr = &builtin_toggle_syntax_highlighting;
	else if (ft_strequ(cmd, "[") || ft_strequ(cmd, "test"))
		*builtin_ret_ptr = &builtin_test;
	else if (ft_strequ(cmd, "alias"))
		*builtin_ret_ptr = &builtin_alias;
	else if (ft_strequ(cmd, "read"))
		*builtin_ret_ptr = &builtin_read;
	else if (ft_strequ(cmd, "unalias"))
		*builtin_ret_ptr = &builtin_unalias;
}

int			is_builtin(char *cmd, \
			void (**builtin_fun_ptr)(char **, t_environ *, t_exec *))
{
	void		*builtin_ret_ptr;

	builtin_ret_ptr = NULL;
	if (ft_strequ(cmd, "echo"))
		builtin_ret_ptr = &builtin_echo;
	else if (ft_strequ(cmd, "cd"))
		builtin_ret_ptr = &builtin_cd;
	else if (ft_strequ(cmd, "setenv") || ft_strequ(cmd, "export"))
		builtin_ret_ptr = &builtin_setenv;
	else if (ft_strequ(cmd, "unsetenv") || ft_strequ(cmd, "unset"))
		builtin_ret_ptr = &builtin_unsetenv;
	else
		is_builtin_bis(cmd, &builtin_ret_ptr);
	if (builtin_fun_ptr)
		*builtin_fun_ptr = builtin_ret_ptr;
	return ((builtin_ret_ptr) ? (1) : (0));
}
