/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 19:11:19 by cgaspart          #+#    #+#             */
/*   Updated: 2018/10/05 13:52:48 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTOCOMPLETE_H
# define AUTOCOMPLETE_H
# include <forty_two_sh.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <stdbool.h>

typedef struct		s_autoc
{
	int				(*key_function[128])(char buffer[LE_KEY_BUFFER_SIZE],
					struct s_autoc *aut);
	struct s_line	*le;
	struct winsize	win;
	char			**items;
	char			*search;
	bool			dot;
	int				nbr_items;
	int				nbr_items_in_line;
	int				nbr_line;
	int				max_item_len;
	int				menu_selected;
	int				menu_line;
}					t_autoc;

void				autocomplete(struct s_line *le);
char				**autoc_dir(t_autoc *autoc);
int					autoc_menu(t_autoc *autoc, struct s_line *le);
int					autoc_arrow_process(int arrow_mask[3], t_autoc *autoc);
int					autoc_key_reader(t_autoc *autoc);
int					autoc_menu_print_items(t_autoc *autoc,
					struct s_line *le);
void				autoc_menu_print_spaces(int longest, int len,
					struct s_line *le);
void				autoc_push_in_line(struct s_line *le, char *str,
					char *search);
char				autoc_check_path(char *dirname);
bool				autoc_check_dot(char *path);
char				**dir_get_items(char *in, t_autoc *autoc);
char				**dir_get_items_search(char *in, t_autoc *autoc);
char				**order_tab_ascii(char **tabl);
void				init_key_func(t_autoc *autoc);
void				ft_ul_video(char *str);
void				ft_ul(char *str);
void				ft_video(char *str);
void				autoc_mem_free(t_autoc *autoc);
void				autoc_free_items(char **items);

#endif
