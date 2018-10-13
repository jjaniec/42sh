/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_end_lexeme.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 19:11:24 by sbrucker          #+#    #+#             */
/*   Updated: 2018/10/13 20:00:22 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Return the sub_ast' closing' lexeme corresponding at t_lexeme *start
*/

t_lexeme	*find_end_lexeme(t_lexeme *start, const int end_token[])
{
	if (!end_token[1])
		return (find_end_lexeme_solo(start, end_token[0]));
	else
		return (find_lexeme_compete(start, end_token));
}
