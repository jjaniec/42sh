/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <cgaspart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 14:15:19 by cgaspart          #+#    #+#             */
/*   Updated: 2018/11/10 16:43:41 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ECHO_H
# define ECHO_H

# include <forty_two_sh.h>

void	builtin_echo(char **argv, t_environ *env, t_exec *exe);
int		echo_n_opt(int i);
int		echo_a_opt(int i);
int		echo_b_opt(int i);
int		echo_c_opt(int i);
int		echo_f_opt(int i);
#endif
