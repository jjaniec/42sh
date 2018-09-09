/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 19:11:19 by cgaspart          #+#    #+#             */
/*   Updated: 2018/08/28 19:11:20 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTOCOMPLETE_H
# define AUTOCOMPLETE_H
# include <twenty_one_sh.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/ioctl.h>

typedef struct			s_autoc
{
	struct s_line		*le;
	struct winsize		win;
	char					**items;
	int					menu_selected;
	int					menu_line;
	int					menu_cursor;
}							t_autoc;

void	autocomplete(struct s_line *le);
char	**autoc_dir(struct s_line *le);
int	autoc_menu(t_autoc *autoc, struct s_line *le);
char	**dir_get_items(char *in);
char	**order_tab_ascii(char **tabl);
void	ft_ul_video(char *str);
void	ft_ul(char *str);
void	ft_video(char *str);
void	autoc_mem_free(t_autoc *autoc);

#endif
