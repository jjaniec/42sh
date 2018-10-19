/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <cgaspart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 16:53:26 by cgaspart          #+#    #+#             */
/*   Updated: 2018/10/19 23:12:50 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_TABLE_H
# define HASH_TABLE_H
# include <forty_two_sh.h>
# include <dirent.h>

typedef struct    s_entry
{
	char			*key;
	char			*value;
	struct s_entry	*next;
}					t_entry;

typedef struct		s_hashtable
{
	int				size;
	char			**path;
	t_entry			**table;
}					t_hashtable;

t_hashtable				*ht_setup(char **env);
t_hashtable				*ht_create(char **env);
void					free_tab(char **items);
void					free_hashtable(t_hashtable *hashtable);
int						ht_hash(t_hashtable *hashtable, char *key);
char					*ht_get_key_value(t_hashtable *hashtable, char *key);

#endif
