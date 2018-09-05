/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 20:10:04 by cfermier          #+#    #+#             */
/*   Updated: 2018/09/02 20:52:09 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static struct s_history *get_former_newest_elem(struct s_history *history)
{
    while (history->next != NULL)
    {
        history = history->next;
    }
    return (history);
}
/*
static void copy_line_edition_attr(struct s_history *new_elem,
                                            struct s_line *le)
{
	new_elem->cmd_le.line_index = le->line_index;
	new_elem->cmd_le.cursor_index_for_line = le->cursor_index_for_line;
	new_elem->cmd_le.current_cursor_pos = le->current_cursor_pos;
	new_elem->cmd_le.current_cursor_line = le->current_cursor_line;
	new_elem->cmd_le.nb_li_currently_writing = le->nb_li_currently_writing;
	new_elem->cmd_le.nb_car_written_on_last_current_line = \
		le->nb_car_written_on_last_current_line;
}
*/
void    add_history(struct s_line *le)
{
   // bool new = false;
    struct s_history *new_elem;

    if ((new_elem = malloc(sizeof(struct s_history))) == NULL)
    	le_exit("Memory allocation failed\n", "malloc", errno);

    ft_strcpy(new_elem->cmd, le->line);
    new_elem->cmd[le->line_index] = '\0';
    new_elem->next = NULL;

    if (le->his_nb_elem == 0)
	{
        new_elem->prev = NULL;
		le->history = new_elem;
	}
    else
	{
        new_elem->prev = get_former_newest_elem(le->history);
		new_elem->prev->next = new_elem;
	}

    ++(le->his_nb_elem);

   // le->special_case_for_newest_his_elem = false;

  // copy_line_edition_attr(new_elem, le);
}
