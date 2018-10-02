/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weird_trick_to_erase_char.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 18:06:05 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/17 15:14:19 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**	In some situations there is a bug in the terminal for erasing a character.
**	To handle these cases, a 'weird trick' is used by printing a blank space on
**	the character we want to erase.
*/

void	weird_trick_to_erase_char(struct s_line *le)
{
	write(STDOUT_FILENO, " ", sizeof(char));
	tputs(le->tcaps->le, 1, &write_one_char);
	tputs(le->tcaps->nd, 1, &write_one_char);
}
