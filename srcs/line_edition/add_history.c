/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 20:10:04 by cfermier          #+#    #+#             */
/*   Updated: 2018/10/20 15:20:40 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

// debug, affiche la liste chainee de l'historique
static void	his_debug(void)
{
	struct s_history *h = access_le_main_datas()->history;

	while (h->prev != NULL)
		h = h->prev;
	//le_debug("%s", "HIS linked list\n");
	while (h != NULL)
	{
		//le_debug("|%s|\n", h->cmd);
		h = h->next;
	}
	//le_debug("%s","HIS END\n");
}

/*
**	Add a new element at the end of the linked list representing
**	the history.
*/

void	add_history(const char *input, struct s_line *le)
{
	struct s_history	*new;
	size_t				input_len;
	struct s_history	*tmp;

	new = ft_xmalloc(sizeof(struct s_history));
	input_len = ft_strlen(input);
	new->cmd = ft_xstrdup(input);
	if (new->cmd[input_len - 1] == '\n')
		new->cmd[input_len - 1] = '\0';
	tmp = le->history;
	while (tmp->next != NULL)
		tmp = tmp->next;
	new->next = tmp;
	new->prev = tmp->prev;
	if (tmp->prev != NULL)
		tmp->prev->next = new;
	tmp->prev = new;

	his_debug(); // debug
}
