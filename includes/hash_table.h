/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <cgaspart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 16:53:26 by cgaspart          #+#    #+#             */
/*   Updated: 2018/10/22 01:15:26 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_TABLE_H
# define HASH_TABLE_H
# include <forty_two_sh.h>
# include <dirent.h>

t_hashtable				*ht_setup(t_environ *env);
t_hashtable				*ht_create(t_environ *env);
char					**ht_get_path(t_environ *env);
void					ht_update(t_environ *env);
int						ht_tab_len(char **items);
void					ht_free_tab(char **items);
void					free_hashtable(t_hashtable *hashtable);
int						ht_hash(t_hashtable *hashtable, char *key);
char					*ht_get_key_value(t_hashtable *hashtable, char *key);

#endif
