/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lexeme.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 18:48:09 by jjaniec           #+#    #+#             */
/*   Updated: 2018/12/10 19:42:03 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Creates a lexeme struct with type and data
*/

t_lexeme		*create_lexeme(int type[2], char *data,
					int pos, char **lexeme_begin_end_ptrs)
{
	t_lexeme	*e;

	e = NULL;
	if (data && *data)
	{
		e = ft_xmalloc(sizeof(t_lexeme));
		e->type = type[0];
		e->data = data;
		e->type_details = type[1];
		e->lexeme_begin_ptr = lexeme_begin_end_ptrs[0];
		e->lexeme_end_ptr = lexeme_begin_end_ptrs[1];
		e->pos = pos;
		e->next = NULL;
		if (e->type == T_CTRL_OPT)
			env_assigns_status(*"Reset env_assign_status variable", 0);
	}
	else
		free(data);
	return (e);
}
