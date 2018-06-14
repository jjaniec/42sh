/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lexeme.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 18:48:09 by jjaniec           #+#    #+#             */
/*   Updated: 2018/06/14 13:49:13 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Creates a lexeme struct with type and data
*/

t_lexeme		*create_lexeme(size_t type, char *data)
{
	t_lexeme	*e;

	e = malloc(sizeof(t_lexeme));
	e->type = type;
	e->data = data;
	e->next = NULL;
	log_debug("Created elem w/ data |%s| - type : %zu", data, type);
	return (e);
}
