/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env_entries.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 20:50:07 by jjaniec           #+#    #+#             */
/*   Updated: 2018/12/05 19:46:28 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Free environnement entries starting at $env_entries
** and remove their pointers to the environnement ptr tab
** and update elements count, env pointers and last_elem pointer
*/

void	free_env_entries(t_environ *env_struct, t_env_entry *env_entries)
{
	t_env_entry	*prev;

	if (!(env_entries))
		return ;
	prev = env_entries;
	env_struct->last_entry_ptr = env_entries->prev;
	if (env_entries->prev)
		env_entries->prev->next = NULL;
	while (env_entries)
	{
		if (prev == env_entries)
			*(prev->ptr_to_pos_in_environ_tab) = NULL;
		prev = env_entries;
		env_entries = env_entries->next;
		free(prev);
		env_struct->entry_count -= 1;
	}
	if (env_struct->entry_count)
		env_struct->environ[env_struct->entry_count + 1] = NULL;
	else
		env_struct->environ[0] = NULL;
}
