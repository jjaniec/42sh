/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 20:10:04 by cfermier          #+#    #+#             */
/*   Updated: 2018/10/21 17:48:51 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

#if 0
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
#endif

/*
**	Cut the command at the first '\n' found (if there is one).
*/

static void	cut_cmd_at_newline(char *cmd)
{
	while (*cmd != '\0')
	{
		if (*cmd == '\n')
		{
			*cmd = '\0';
			return ;
		}
		++cmd;
	}
}

/*
**	Add a new element at the end of the linked list representing
**	the history.
*/

void		add_history(const char *input, struct s_line *le)
{
	struct s_history	*new;
	struct s_history	*tmp;

	new = ft_xmalloc(sizeof(struct s_history));
	new->cmd = ft_xstrdup(input);
	//if (new->cmd[input_len - 1] == '\n')
		//new->cmd[input_len - 1] = '\0';
	cut_cmd_at_newline(new->cmd);
	tmp = le->history;
	while (tmp->next != NULL)
		tmp = tmp->next;
	new->next = tmp;
	new->prev = tmp->prev;
	if (tmp->prev != NULL)
		tmp->prev->next = new;
	tmp->prev = new;

//	his_debug(); // debug
}
