/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   good_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebastien <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 17:30:40 by sebastien         #+#    #+#             */
/*   Updated: 2018/09/26 11:06:59 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Defines if the current lexeme with associated token is a good start \
** after the IF or ELIF or WHILE (for a T_SCRIPT_CONDITION)
*/

int		good_start(t_lexeme *lex)
{
	int		i;

	i = 0;
	while (g_cant_begin_with[i])
	{
		if (lex->type_details == g_cant_begin_with[i])
			return (0);
		i++;
	}
	return (1);
}
