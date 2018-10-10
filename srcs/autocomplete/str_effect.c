/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_effect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 19:33:08 by cgaspart          #+#    #+#             */
/*   Updated: 2018/10/05 13:54:50 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

void	ft_ul_video(char *str)
{
	tputs(tgetstr("us", NULL), 1, &write_one_char);
	tputs(tgetstr("mr", NULL), 1, &write_one_char);
	ft_putstr(str);
	tputs(tgetstr("me", NULL), 1, &write_one_char);
	tputs(tgetstr("ue", NULL), 1, &write_one_char);
}

void	ft_ul(char *str)
{
	tputs(tgetstr("us", NULL), 1, &write_one_char);
	ft_putstr(str);
	tputs(tgetstr("ue", NULL), 1, &write_one_char);
}

void	ft_video(char *str)
{
	tputs(tgetstr("mr", NULL), 1, &write_one_char);
	ft_putstr(str);
	tputs(tgetstr("me", NULL), 1, &write_one_char);
}
