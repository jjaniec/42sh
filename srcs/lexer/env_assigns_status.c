/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_assigns_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 20:29:09 by jjaniec           #+#    #+#             */
/*   Updated: 2018/06/22 20:38:43 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Controls value of the env_assigns_passed variable, which determines
** if the T_ENV_ASSIGN type can be set to strings containing the '=' char
*/

int		env_assigns_status(int mode_set, int mode_set_value)
{
	static int		env_assigns_passed = 0;

	if (mode_set)
		env_assigns_passed = mode_set_value;
	return (env_assigns_passed);
}
