/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_char_into_array.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 17:53:09 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/17 13:31:26 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
**	Insert a character in the command line's buffer.
*/

void	insert_char_into_array(struct s_line *le, t_kno key, unsigned int pos)
{
	check_cmd_storage(le, 2);
	ft_memmove(le->line + pos + 1, le->line + pos, ft_strlen(le->line + pos));
	le->line[pos] = key;
}
