/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sigwinch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 16:01:49 by cfermier          #+#    #+#             */
/*   Updated: 2018/09/17 13:05:08 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**	Handler function for the WINCH signal.
**	The window is cleared, then the prompt is reprinted and
**	the current command line is reprinted too.
*/

// NOT DONE YET
void	handle_sigwinch(int sig)
{
	if (sig != SIGWINCH)
		return ;
	
}

