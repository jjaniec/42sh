/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lexemes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 12:37:51 by jjaniec           #+#    #+#             */
/*   Updated: 2018/07/04 12:48:10 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void		free_lexemes(t_lexeme *ll)
{
	t_lexeme	*prev;
	while (ll)
	{
		free(ll->data);
		prev = ll;
		ll = ll->next;
		free (prev);
	}
}