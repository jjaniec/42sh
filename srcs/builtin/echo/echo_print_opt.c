/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_print_opt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <cgaspart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 16:51:37 by cgaspart          #+#    #+#             */
/*   Updated: 2018/12/03 20:45:29 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

int		echo_print_opt(t_exec *exe, char *str)
{
	int		ret;
	int		(*opt_func[128])();

	init_flag_opt(opt_func);
	str++;
	ret = opt_func[(int)(*str)]();
	if (ret == -2)
	{
		exe->ret = 1;
		return (-1);
	}
	else if (ret == -1)
		return (-1);
	return (1);
}
