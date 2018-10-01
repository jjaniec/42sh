/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_end_lexeme.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 19:11:24 by sbrucker          #+#    #+#             */
/*   Updated: 2018/09/20 19:43:14 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Return the sub_ast' closing' lexeme corresponding at t_lexeme *start
*/

t_lexeme	*find_end_lexeme(t_lexeme *start, const size_t end_token[])
{
	if (!end_token[1])
		return (find_end_lexeme_solo(start, end_token[0]));
	else
		return (find_lexeme_compete(start, end_token));
}
