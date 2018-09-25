/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 15:57:17 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/25 21:19:24 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** If $entry_value contains '=', entry will directly be stored, no need to set name
*/

static void	upd_self_ptrs(t_environ *self, t_env_entry *new_entry_struct)
{
	self->last_used_elem = new_entry_struct;
	self->environ[self->entry_count] = new_entry_struct->entry;
	new_entry_struct->ptr_to_pos_in_environ_tab = &(self->environ[self->entry_count]);
	self->environ[++self->entry_count] = NULL;
	if (self->last_entry_ptr)
		self->last_entry_ptr->next = new_entry_struct;
	self->last_entry_ptr = new_entry_struct;
	new_entry_struct->next = NULL;
	if (!(self->env_entries_list))
		self->env_entries_list = new_entry_struct;
}

char		*add_env_var(t_environ *self, char *entry_value, char *name)
{
	int				i;
	char			*assign_char_ptr;
	t_env_entry		*new_entry_struct;
	int				entry_name_len;

	if (self->entry_count == MAX_ENV_ENTRIES)
		return (NULL);
	new_entry_struct = malloc(sizeof(t_env_entry));
	new_entry_struct->next = NULL;
	new_entry_struct->ptr_to_pos_in_environ_tab = NULL;
	i = 0;
	if ((assign_char_ptr = ft_strchr(entry_value, '=')) && assign_char_ptr != entry_value)
		ft_strncpy(new_entry_struct->entry, entry_value, MAX_ENV_ENTRY_LEN);
	else if (name && *name)
	{
		entry_name_len = ft_strlen(name);
		ft_strncpy(new_entry_struct->entry, name, \
			(MAX_ENV_ENTRY_LEN < entry_name_len) ? (MAX_ENV_ENTRY_LEN) : (entry_name_len));
		new_entry_struct->entry[entry_name_len] = '=';
		ft_strncpy(new_entry_struct->entry + entry_name_len + 1, entry_value, \
			(MAX_ENV_ENTRY_LEN < entry_name_len) ? (MAX_ENV_ENTRY_LEN) : (entry_name_len));
	}
	new_entry_struct->entry[MAX_ENV_ENTRY_LEN] = '\0';
	log_fatal("new_entry_struct->entry : |%s|", new_entry_struct->entry);
	upd_self_ptrs(self, new_entry_struct);
	return (new_entry_struct->entry);
}
