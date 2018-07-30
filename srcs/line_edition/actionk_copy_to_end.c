/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_copy_to_end.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfermier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 13:14:46 by cfermier          #+#    #+#             */
/*   Updated: 2018/07/30 13:14:46 by cfermier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

void    actionk_copy_to_end(struct s_line *le)
{
    //le->clipboard[0] = '\0';
   // ft_strncat( le->clipboard, \
   // &(le->line[le->cursor_index_for_line + 1]), \
   // le->line_index - le->cursor_index_for_line);
    ft_strcpy(le->clipboard, &(le->line[le->cursor_index_for_line + 1]));
    fprintf(tty_debug, "CLIPBOARD = |%s|\n", le->clipboard);
}
