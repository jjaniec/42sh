/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_color_id.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 15:27:43 by jjaniec           #+#    #+#             */
/*   Updated: 2018/02/14 18:32:00 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Print defined color ID to enable terminal color
*/

static void		ft_print_color_id_bg(char *cl, int attr)
{
	if (attr == 1 && !ft_strcmp(cl, "DARK_GREY"))
		ft_putstr(BG_DARK_GREY);
	if (attr == 2 || attr == 0)
	{
		if (!ft_strcmp(cl, "DEFAULT"))
			ft_putstr((BG_DEFAULT));
		if (!ft_strcmp(cl, "BLACK"))
			ft_putstr((BG_BLACK));
		if (!ft_strcmp(cl, "RED"))
			ft_putstr((attr == 1) ? (BG_LIGHT_RED) : (BG_RED));
		if (!ft_strcmp(cl, "GREEN"))
			ft_putstr((attr == 1) ? (BG_LIGHT_GREEN) : (BG_GREEN));
		if (!ft_strcmp(cl, "YELLOW"))
			ft_putstr((attr == 1) ? (BG_LIGHT_YELLOW) : (BG_YELLOW));
		if (!ft_strcmp(cl, "BLUE"))
			ft_putstr((attr == 1) ? (BG_LIGHT_BLUE) : (BG_BLUE));
		if (!ft_strcmp(cl, "MAGENTA"))
			ft_putstr((attr == 1) ? (BG_LIGHT_MAGENTA) : (BG_MAGENTA));
		if (!ft_strcmp(cl, "CYAN"))
			ft_putstr((attr == 1) ? (BG_LIGHT_CYAN) : (BG_CYAN));
	}
}

static void		ft_print_color_id_fg(char *cl, int attr)
{
	if (attr == 1 && !ft_strcmp(cl, "DARK_GREY"))
		ft_putstr(FG_DARK_GREY);
	if (attr == 2 || attr == 0)
	{
		if (!ft_strcmp(cl, "DEFAULT"))
			ft_putstr((FG_DEFAULT));
		if (!ft_strcmp(cl, "BLACK"))
			ft_putstr((FG_BLACK));
		if (!ft_strcmp(cl, "RED"))
			ft_putstr((attr == 1) ? (FG_LIGHT_RED) : (FG_RED));
		if (!ft_strcmp(cl, "GREEN"))
			ft_putstr((attr == 1) ? (FG_LIGHT_GREEN) : (FG_GREEN));
		if (!ft_strcmp(cl, "YELLOW"))
			ft_putstr((attr == 1) ? (FG_LIGHT_YELLOW) : (FG_YELLOW));
		if (!ft_strcmp(cl, "BLUE"))
			ft_putstr((attr == 1) ? (FG_LIGHT_BLUE) : (FG_BLUE));
		if (!ft_strcmp(cl, "MAGENTA"))
			ft_putstr((attr == 1) ? (FG_LIGHT_MAGENTA) : (FG_MAGENTA));
		if (!ft_strcmp(cl, "CYAN"))
			ft_putstr((attr == 1) ? (FG_LIGHT_CYAN) : (FG_CYAN));
	}
}

void			ft_print_color_id(char *cl, int *tab)
{
	if (tab[0] == 0 || tab[0] == 1)
		ft_print_color_id_fg(cl + ((tab[1] == 2) ? (6) : (0)), tab[1]);
	if (tab[0] == 2)
		ft_print_color_id_bg(cl + ((tab[1] == 2) ? (6) : (0)), tab[1]);
}
