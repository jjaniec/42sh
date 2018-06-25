/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_termcaps_strings.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 20:00:25 by cyfermie          #+#    #+#             */
/*   Updated: 2018/06/25 20:48:49 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

struct s_le_termcaps	*init_termcaps_strings(void)
{
	static struct s_le_termcaps tc;

	if ((tc.nd = tgetstr("nd", NULL)) == NULL)
		le_exit("Failed to initialize \"nd\" termcap\n", "tgetstr");
	if ((tc.le = tgetstr("le", NULL)) == NULL)
		le_exit("Failed to initialize \"le\" termcap\n", "tgetstr");

	return (&tc);
}
