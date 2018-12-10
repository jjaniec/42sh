/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_free_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <cgaspart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 19:47:50 by cgaspart          #+#    #+#             */
/*   Updated: 2018/11/27 16:27:51 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void	cd_free_struct(t_cd *cd_i)
{
	if (cd_i->cwd_link)
		free(cd_i->cwd_link);
	free(cd_i->cwd);
	free(cd_i);
}
