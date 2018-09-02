/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_copy_to_end.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 13:14:46 by cfermier          #+#    #+#             */
/*   Updated: 2018/09/02 20:52:00 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void    actionk_copy_to_end(struct s_line *le)
{
    //le->clipboard[0] = '\0';
   // ft_strncat( le->clipboard, 
   // &(le->line[le->cursor_index_for_line + 1]), 
   // le->line_index - le->cursor_index_for_line);
    ft_strcpy(le->clipboard, &(le->line[le->cursor_index_for_line + 1]));
    fprintf(tty_debug, "CLIPBOARD = |%s|\n", le->clipboard);
}
