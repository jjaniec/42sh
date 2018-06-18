/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lexeme.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 18:48:09 by jjaniec           #+#    #+#             */
/*   Updated: 2018/06/18 19:24:55 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Creates a lexeme struct with type and data
*/

t_lexeme		*create_lexeme(size_t type, char *data, size_t type_details)
{
	t_lexeme	*e;

	e = NULL;
	if (data && *data)
	{
		e = malloc(sizeof(t_lexeme));
		e->type = type;
		e->data = data;
		e->type_details = type_details;
		e->next = NULL;
		log_info("Created elem w/ data |%s| - type : %zu", data, type);
	}
	else
		log_warn("Skipping creation of empty data element");
	return (e);
}
