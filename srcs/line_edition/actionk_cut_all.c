/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_cut_all.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 18:19:51 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/02 20:52:06 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
**	The command line is entirely copied into the shell clipboard, and
**	entirely cleared. If the command line is empty, it does nothing and
**	the clipboard remains untouched.
*/

void	actionk_cut_all(struct s_line *le)
{
	if (le->line[0] == '\0')
		return ;

	actionk_copy_all(le);
	actionk_delete_current_input(le);
}
