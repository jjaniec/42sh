/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_free_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <cgaspart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 19:47:50 by cgaspart          #+#    #+#             */
/*   Updated: 2018/11/21 19:59:13 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

void	cd_free_struct(t_cd *cd_i)
{
	ft_putstr_fd("ESH1\n", 2);
	if (cd_i->cwd_link)
		free(cd_i->cwd_link);
	ft_putstr_fd("ESH2\n", 2);
	free(cd_i->cwd);
	ft_putstr_fd("ESH3\n", 2);
	free(cd_i);
	ft_putstr_fd("ESH4\n", 2);
}
