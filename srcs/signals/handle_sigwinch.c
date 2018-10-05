/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sigwinch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 16:01:49 by cfermier          #+#    #+#             */
/*   Updated: 2018/09/30 21:18:30 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**	Handler function for the WINCH signal.
**	The window is cleared, then the prompt is reprinted and
**	the current command line will be reprinted too.
*/

void	handle_sigwinch(int sig)
{
	struct s_line	*le;

	le = access_le_main_datas();
	if (sig != SIGWINCH)
		return ;
	if (g_cmd_status.cmd_running == true)
		return ;
	else
	{
		if ((g_cmd_status.keep_le_main_datas = malloc(sizeof(struct s_line))) == NULL)
			le_exit("Memory allocation failed\n", "malloc", errno);
		ft_memcpy(g_cmd_status.keep_le_main_datas, le, sizeof(struct s_line));
		g_cmd_status.resize_happened = true;
		tputs(le->tcaps->cl, 1, &write_one_char);
	}
}
