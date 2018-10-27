/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   good_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 17:30:40 by sebastien         #+#    #+#             */
/*   Updated: 2018/10/19 19:48:11 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Defines if the current lexeme with associated token is a good start \
** after the IF or ELIF or WHILE (for a T_SCRIPT_CONDITION)
*/

int		good_start(t_lexeme *lex)
{
	unsigned int	i;

	i = 0;
	while (g_cant_begin_with[i])
	{
		if (lex->type_details == g_cant_begin_with[i])
			return (0);
		i++;
	}
	return (1);
}
