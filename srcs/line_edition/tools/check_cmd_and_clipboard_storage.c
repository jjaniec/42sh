/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_and_clipboard_storage.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 18:11:36 by cyfermie          #+#    #+#             */
/*   Updated: 2018/10/20 15:54:05 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**	Check if there is enough space in the shell's clipboard buffer
**	to store 'nb_char' more chatacters in it.
**	If no, the shell's clipboard buffer is reallocated by multiplying
**	the buffer's size by 2, and as many times as necessary.
*/

void	check_clipboard_storage(struct s_line *le, unsigned int nb_char)
{
	void	*tmp_realloc;

	while (le->clipboard_len + nb_char + 1 >= le->clipboard_size)
	{
		//fprintf(tty_debug, "REALLOCATION DE LA MEMOIRE DE L\'ORDINATEUR clipboard\n");
		tmp_realloc = ft_xrealloc(le->clipboard, le->clipboard_size, \
		le->clipboard_size * 2);
		le->clipboard = tmp_realloc;
		le->clipboard_size *= 2;
		ft_memset(le->clipboard + le->clipboard_len, '\0', \
		le->clipboard_size - le->clipboard_len);
	}
}

/*
**	Check if there is enough space in the command line's buffer
**	to store 'nb_char' more chatacters in it.
**	If no, the command line's buffer is reallocated by multiplying
**	the buffer's size by 2, and as many times as necessary.
*/

void	check_cmd_storage(struct s_line *le, unsigned int nb_char)
{
	void	*tmp_realloc;

	while (le->cmd_len + nb_char + 1 >= le->cmd_size)
	{
		//fprintf(tty_debug, "REALLOCATION DE LA MEMOIRE DE L\'ORDINATEUR\n");
		tmp_realloc = ft_xrealloc(le->cmd, le->cmd_size, le->cmd_size * 2);
		le->cmd = tmp_realloc;
		le->cmd_size *= 2;
		ft_memset(le->cmd + le->cmd_len, '\0', \
		le->cmd_size - le->cmd_len);
	}
}
