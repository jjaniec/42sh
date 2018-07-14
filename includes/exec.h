/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 13:04:09 by sbrucker          #+#    #+#             */
/*   Updated: 2018/07/12 11:36:12 by sebastien        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <twenty_one_sh.h>

int		exec_cmd(t_ast *root, char **envp);
void	exec_argv(char **argv, char **envp, t_exec *exe, t_ast *node);
t_exec	*exec_thread(char *cmd, char **argv, char **envp, t_exec *exe, t_ast *node);
t_exec	*pre_exec(t_ast *node, t_exec *exe);
t_exec	*in_exec(t_ast *node, t_exec *exe);
t_exec	*post_exec(t_ast *node, t_exec *exe);
void	exec_local(char **argv, char **envp, t_exec *exe, t_ast *node);
void	exec_builtin(char **argv, char **envp, t_exec *exe);
void	exec_binary(char **argv, char **envp, t_exec *exe, t_ast *node);
int		is_builtin(char *cmd);

void	io_manager_in(t_ast *node, t_exec *exe);
void	io_manager_pre(t_ast *node, t_exec *exe);

char	*get_env(const char *name, const char **envp);
int		get_env_pos(const char *name, const char **envp);
size_t	size_envp(const char **envp);
char	**cp_envp(const char **envp);
void	show_envp(char **envp);
char	*new_path(char *s1, char *s2);
char	**get_path(char *str);
char	*isin_path(char **paths, char *cmd);

void	builtin_exit(t_exec *exe);
void	builtin_echo(char **argv, char **envp);
void	builtin_env(char **argv, char **envp, t_exec *exe);
void	builtin_setenv(char **argv, char **envp, t_exec *exe);
void	builtin_unsetenv(char **argv, char **envp, t_exec *exe);
void	builtin_cd(char **argv, char **envp, t_exec *exe);

char	**inline_setenv(char *name, char *value, char **envp);
char	**inline_unsetenv(char *name, char **envp);

void	handle_redirs(t_ast *redir_ast_node);
void	free_exec(t_exec **exe);

#endif
