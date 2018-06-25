/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 13:04:09 by sbrucker          #+#    #+#             */
/*   Updated: 2018/06/25 13:38:52 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <twenty_one_sh.h>

int		exec_cmd(t_ast *root, char **envp);
t_exec	*exec_thread(char *cmd, char **argv, t_exec *exe);
t_exec	*pre_exec(t_ast *node, t_exec *exe);
t_exec	*in_exec(t_ast *node, t_exec *exe);
t_exec	*post_exec(t_ast *node, t_exec *exe);

char	*get_env(const char *name, const char **envp);
size_t	size_envp(const char **envp);
char	**cp_envp(const char **envp);
void	show_envp(char **envp);
char	*new_path(char *s1, char *s2);
char	**get_path(char *str);
char	*isin_path(char **paths, char *cmd);

#endif
