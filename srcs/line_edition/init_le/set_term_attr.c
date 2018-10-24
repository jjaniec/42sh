/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_term_attr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 19:21:17 by cyfermie          #+#    #+#             */
/*   Updated: 2018/10/20 15:51:32 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**	Modifying the terminal's settings
*/

static void		init_termios_flags(struct termios *new)
{
	new->c_lflag &= ~(ECHO | ICANON);
	new->c_lflag |= ISIG;
	new->c_oflag &= ~(OPOST);
	new->c_cc[VMIN] = 1;
	new->c_cc[VTIME] = 0;
}

/*
**	LE_SET_NEW mode : The current terminal's settings are saved, and new
**	settings are set.
**
**	LE_SET_OLD : The saved settings are restored the way they were.
*/

void			set_term_attr(t_set_term mode)
{
	static struct termios	old;
	struct termios			new;

	if (mode == LE_SET_NEW)
	{
		if (tcgetattr(STDIN_FILENO, &old) == -1)
		{
			ft_putstr_fd("Error while getting terminal attributes\n", 2);
			exit(EXIT_FAILURE);
		}
		new = old;
		init_termios_flags(&new);
		if (tcsetattr(STDIN_FILENO, TCSADRAIN, &new) == -1)
		{
			ft_putstr_fd("Error while setting terminal attributes\n", 2);
			exit(EXIT_FAILURE);
		}
	}
	else if (mode == LE_SET_OLD)
		if (tcsetattr(STDIN_FILENO, TCSADRAIN, &old) == -1)
		{
			ft_putstr_fd("Error while setting terminal attributes\n", 2);
			exit(EXIT_FAILURE);
		}
}
