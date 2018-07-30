/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_copy_to_start.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfermier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 12:41:38 by cfermier          #+#    #+#             */
/*   Updated: 2018/07/30 12:41:38 by cfermier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

void    actionk_copy_to_start(struct s_line *le)
{
    le->clipboard[0] = '\0';
    ft_strncat( le->clipboard, &(le->line[0]), le->cursor_index_for_line );
    fprintf(tty_debug, "CLIPBOARD = |%s|\n", le->clipboard);
}
