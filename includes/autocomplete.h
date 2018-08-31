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

typedef struct			s_select
{
	char					*name;
	int					selected;
	struct s_select	*next;
}							t_select;

void	autocomplete(struct s_line *le);
char	**autoc_dir(struct s_line *le);
char	**dir_get_items(char *in);
char	**order_tab_ascii(char **tabl);
void	ft_ul_video(char *str);
void	ft_ul(char *str);
void	ft_video(char *str);

#endif
