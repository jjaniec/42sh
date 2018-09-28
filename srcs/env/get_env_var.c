/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 13:28:48 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/26 20:17:30 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Return pointer to t_env_entry struct w/ corresponding name in self->environ
*/

t_env_entry		*get_env_var(t_environ *self, char *varname)
{
	t_env_entry	*ptr;

	if (!(self && self->env_entries_list && (ptr = self->env_entries_list)))
		return (NULL);
	while (ptr && ft_strcmp(ptr->entry, varname) != 61)
		ptr = ptr->next;
	if (ptr)
	{
		log_debug("Found %s env var w/ data %s", varname, ptr->entry);
		self->last_used_elem = ptr;
	}
	else
		log_error("%s environnement variable not found !", varname);
	return (ptr);
}
