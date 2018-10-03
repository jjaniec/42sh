/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_char_into_array.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 17:53:09 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/17 17:30:47 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**	Insert a character in the command line's buffer.
*/

void	insert_char_into_array(struct s_line *le, t_kno key, unsigned int pos)
{
	check_cmd_storage(le, 2);
	ft_memmove(le->cmd + pos + 1, le->cmd + pos, ft_strlen(le->cmd + pos));
	le->cmd[pos] = key;
}
