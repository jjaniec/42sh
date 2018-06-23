/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_term_attr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 19:21:17 by cyfermie          #+#    #+#             */
/*   Updated: 2018/06/23 16:43:43 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

/*
**	set_term_attr() can be call with :
**	 SET_NEW to save current attributes and set 42sh attributes
**	 SET_OLD to set the saved attributes
*/

static void		init_termcaps(void)
{
	const char	*term;

	if ((term = getenv("TERM")) == NULL)
		term = "xterm-256color";
	if (tgetent(NULL, term) != 1)
		le_exit("Error while getting terminal attributes\n", "tgetent");
}

static void		init_termios_flags(struct termios *new)
{
	new->c_lflag &= ~(ECHO | ICANON);
	new->c_lflag |= ISIG;
	new->c_oflag &= ~(OPOST);
	new->c_cc[VMIN] = 1;
	new->c_cc[VTIME] = 0;
}

void			set_term_attr(t_set_term mode)
{
	static struct termios	old;
	struct termios			new;

	if (mode == SET_NEW)
	{
		if (tcgetattr(STDIN_FILENO, &old) == -1)
			le_exit("Error while getting terminal attributes\n", "tcgetattr");
		new = old;
		init_termios_flags(&new);
		if (tcsetattr(STDIN_FILENO, TCSADRAIN, &new) == -1)
			le_exit("Error while setting terminal attributes\n", "tcsetattr");
		init_termcaps();
	}
	else if (mode == SET_OLD)
	{
		if (tcsetattr(STDIN_FILENO, TCSADRAIN, &old) == -1)
			le_exit("Error while setting terminal attributes\n", "tcsetattr");
	}
}
