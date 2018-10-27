/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 14:10:32 by cyfermie          #+#    #+#             */
/*   Updated: 2018/10/22 19:39:59 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <forty_two_sh.h>


# define BUILTIN_ENV_USAGE \
	SH_NAME ": env [-i][name=value]...	[utility [argument...]]"

# define BUILTIN_CD_USAGE \
	SH_NAME ": cd [-L | -P] [-] [directory]"

# define BUILTIN_TEST_USAGE \
	SH_NAME ": test, [ --\n\t\ttest expression\n\t\t[ expression ]\n\t\t! expression"

# define BUILTIN_HISTORY_USAGE \
	SH_NAME ": Usage : history [n | -d n | --clear | --save]\n"

# define BUILTIN_ALIAS_USAGE \
	SH_NAME ": usage: alias [-d] key value | --save\n"

# define BUILTIN_SETENV_USAGE \
	SH_NAME ": setenv: usage setenv VAR1=VALUE1 VAR2=VALUE2 ...\n"

# define BUILTIN_UNSETENV_USAGE \
	SH_NAME ": unsetenv: usage unsetenv VAR1NAME VAR2NAME ...\n"

# define BUILTIN_READ_USAGE \
	SH_NAME ": read: usage read [-d 'x'] [[-n | -N] x] -p -s -- VAR1 VAR2 ...\n"
#define BLTREAD_MAX_CH (10U)

struct s_alias
{
	char			*key;
	char			*value;
	struct s_alias	*next;
};

struct s_bltread
{
	bool			opt_d;
	unsigned int	delim_opt_d;
	bool			opt_n;
	bool			opt_N;
	unsigned int	nb_opt_nN;
	bool			opt_p;
	bool			opt_s;
	char			**words_vars;
};

int		is_builtin(char *cmd, void (**builtin_fun_ptr)(char **, t_environ *, t_exec *));
void	builtin_exit(char **argv, t_environ *env, t_exec *exe);
void	builtin_echo(char **argv, t_environ *env, t_exec *exe);
void	builtin_env(char **argv, t_environ *env, t_exec *exe);
void	builtin_setenv(char **argv, t_environ *env, t_exec *exe);
void	builtin_unsetenv(char **argv, t_environ *env, t_exec *exe);
void	builtin_cd(char **argv, t_environ *env, t_exec *exe);
void	builtin_return(char **argv, t_environ *env, t_exec *exe);
void	builtin_toggle_syntax_highlighting(char **argv, t_environ *env, t_exec *exe);
void	builtin_test(char **argv, t_environ *env, t_exec *exe);
void	builtin_history(char **argv, t_environ *env, t_exec *exe);
void	builtin_toggle_syntax_highlighting(char **argv, t_environ *env, t_exec *exe);
void	builtin_alias(char **argv, t_environ *env, t_exec *exe);
void    builtin_read(char **argv, t_environ *env, t_exec *exe);
void    builtin_unalias(char **argv, t_environ *env, t_exec *exe);

#endif
