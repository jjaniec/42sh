/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 20:10:04 by cfermier          #+#    #+#             */
/*   Updated: 2018/09/13 16:27:12 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void	his_debug(void)
{
	struct s_history *h = access_le_main_datas()->history;

	while (h->prev != NULL)
		h = h->prev;

	fprintf(tty_debug, "HIS linked list\n");
	while (h != NULL)
	{
		fprintf(tty_debug, "|%s|\n", h->cmd);
		h = h->next;
	}
	fprintf(tty_debug, "HIS END\n");

}

static struct s_history *get_former_newest_elem(struct s_history *history)
{
    while (history->next != NULL)
    {
        history = history->next;
    }
    return (history);
}



void	add_history(const char *input, struct s_line *le)
{
	struct s_history	*new;

	new = malloc(sizeof(struct s_history)); // check ret
	
	size_t input_len = ft_strlen(input);
	new->cmd = ft_strdup(input); // check ret
	if (new->cmd[input_len - 1] == '\n')
		new->cmd[input_len - 1] = '\0';

	struct s_history *tmp = le->history;
	while (tmp->next != NULL)
		tmp = tmp->next;
	new->next = tmp;
	new->prev = tmp->prev;
	if (tmp->prev != NULL)
		tmp->prev->next = new;
	tmp->prev = new;
	
	++(le->his_nb_elem);

	his_debug();
	
}




void    old_add_history(struct s_line *le)
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
