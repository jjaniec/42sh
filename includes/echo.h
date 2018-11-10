/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <cgaspart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 14:15:19 by cgaspart          #+#    #+#             */
/*   Updated: 2018/11/10 21:53:05 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ECHO_H
# define ECHO_H

# include <forty_two_sh.h>

void	builtin_echo(char **argv, t_environ *env, t_exec *exe);
int		echo_n_opt(void);
int		echo_a_opt(void);
int		echo_b_opt(void);
int		echo_c_opt(void);
int		echo_f_opt(void);
int		echo_r_opt(void);
int		echo_t_opt(void);
int		echo_v_opt(void);
int		echo_bslash_opt(void);
#endif
