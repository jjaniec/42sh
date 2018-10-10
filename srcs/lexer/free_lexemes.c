/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lexemes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 12:37:51 by jjaniec           #+#    #+#             */
/*   Updated: 2018/10/07 17:12:07 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Free lexemes linked list
*/

void		free_lexemes(t_lexeme *ll)
{
	t_lexeme	*prev;

	while (ll)
	{
		free(ll->data);
		prev = ll;
		ll = ll->next;
		free(prev);
	}
}
