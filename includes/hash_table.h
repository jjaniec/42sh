/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 16:53:26 by cgaspart          #+#    #+#             */
/*   Updated: 2018/10/09 16:53:31 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_TABLE_H
# define HASH_TABLE_H
# include <forty_two_sh.h>
# include <dirent.h>

typedef struct    s_entry
{
	char            *key;
	char			      *value;
	struct s_entry	*next;
}					        t_entry;

typedef struct    s_hashtable
{
	int		          size;
	t_entry	        **table;
}                 t_hashtable;

void              ht_setup(char **env);
void		          free_tab(char **items);

#endif
