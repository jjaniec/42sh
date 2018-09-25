/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 20:26:17 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/25 21:30:02 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static void			delete_from_environ_ptr_tab(t_env_entry *entry_to_del_ptr)
{
	char		**environ_ptr;

	environ_ptr = entry_to_del_ptr->ptr_to_pos_in_environ_tab;
	log_trace("del %s", *environ_ptr);
	while (*environ_ptr)
	{
		*environ_ptr = *(environ_ptr + 1);
		environ_ptr++;
	}
}

static void			remove_env_entry(t_environ *self, t_env_entry *prev_entry)
{
	t_env_entry	*entry_to_del_ptr;

	self->last_used_elem = NULL;
	if (prev_entry)
	{
		entry_to_del_ptr = prev_entry->next;
		prev_entry->next = prev_entry->next->next;
	}
	else
	{
		entry_to_del_ptr = self->env_entries_list;
		self->env_entries_list = self->env_entries_list->next;
	}
	delete_from_environ_ptr_tab(entry_to_del_ptr);
	free(entry_to_del_ptr);
}

static t_env_entry	*env_entry_name_search(t_env_entry *env_entries_list, \
						char *varname, t_env_entry **prev)
{
	t_env_entry	*ptr;

	if (!(ptr = env_entries_list))
		return (NULL);
	*prev = NULL;
	while (ptr && ft_strcmp(ptr->entry, varname) != 61)
	{
		*prev = ptr;
		ptr = ptr->next;
	}
	return (ptr);
}

int					del_env_var(struct s_environ *self, char *var_name)
{
	t_env_entry	*cur_env_var_struct;
	t_env_entry	*elem_before_entry_elem;

	log_trace("Deleting |%s| from env", var_name);
	cur_env_var_struct = \
		env_entry_name_search(self->env_entries_list, var_name, &elem_before_entry_elem);
	if (!cur_env_var_struct)
		return (1);
	log_trace("Var |%s| from env", cur_env_var_struct->entry);
	remove_env_entry(self, elem_before_entry_elem);
	return (0);
}
