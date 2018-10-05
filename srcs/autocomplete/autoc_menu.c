/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autoc_menu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 16:22:54 by cgaspart          #+#    #+#             */
/*   Updated: 2018/10/05 13:54:24 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

int							autoc_menu(t_autoc *autoc, struct s_line *le)
{
	if (autoc_menu_print_items(autoc, le))
		return (0);
	init_key_func(autoc);
	while (autoc_key_reader(autoc))
		autoc_menu_print_items(autoc, le);
	return (1);
}
