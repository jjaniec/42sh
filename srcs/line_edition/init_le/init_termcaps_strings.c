/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_termcaps_strings.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 20:00:25 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/17 13:19:36 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
**	Initialize some termcaps that will be used for the shell internal behavior.
*/

struct s_le_termcaps	*init_termcaps_strings(void)
{
	static struct s_le_termcaps tc;
	
	if ((tc.nd = tgetstr("nd", NULL)) == NULL)
		le_exit("Failed to initialize \"nd\" termcap\n", "tgetstr", errno);
	if ((tc.le = tgetstr("le", NULL)) == NULL)
		le_exit("Failed to initialize \"le\" termcap\n", "tgetstr", errno);
	if ((tc._do = tgetstr("do", NULL)) == NULL)
		le_exit("Failed to initialize \"do\" termcap\n", "tgetstr", errno);
	if ((tc.up = tgetstr("up", NULL)) == NULL)
		le_exit("Failed to initialize \"up\" termcap\n", "tgetstr", errno);
	if ((tc.dc = tgetstr("dc", NULL)) == NULL)
		le_exit("Failed to initialize \"dc\" termcap\n", "tgetstr", errno);
	if ((tc.cl = tgetstr("cl", NULL)) == NULL)
		le_exit("Failed to initialize \"cl\" termcap\n", "tgetstr", errno);

	return (&tc);
}
