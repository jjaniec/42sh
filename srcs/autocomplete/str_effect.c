/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_effect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 19:33:08 by cgaspart          #+#    #+#             */
/*   Updated: 2018/10/20 18:38:42 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

void	ft_ul_video(char *str)
{
	tputs(access_le_main_datas()->tcaps->us, 1, &write_one_char);
	tputs(access_le_main_datas()->tcaps->mr, 1, &write_one_char);
	ft_putstr(str);
	tputs(access_le_main_datas()->tcaps->me, 1, &write_one_char);
	tputs(access_le_main_datas()->tcaps->ue, 1, &write_one_char);
}

void	ft_ul(char *str)
{
	tputs(access_le_main_datas()->tcaps->us, 1, &write_one_char);
	ft_putstr(str);
	tputs(access_le_main_datas()->tcaps->ue, 1, &write_one_char);
}

void	ft_video(char *str)
{
	tputs(access_le_main_datas()->tcaps->mr, 1, &write_one_char);
	ft_putstr(str);
	tputs(access_le_main_datas()->tcaps->me, 1, &write_one_char);
}
