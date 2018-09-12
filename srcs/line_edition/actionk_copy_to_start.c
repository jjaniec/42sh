/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_copy_to_start.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 12:41:38 by cfermier          #+#    #+#             */
/*   Updated: 2018/09/02 20:52:06 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void    actionk_copy_to_start(struct s_line *le)
{
    le->clipboard_len = 0;
    check_clipboard_storage(le, le->cursor_index_for_line + 1);

    le->clipboard[0] = '\0';
    ft_strncat( le->clipboard, &(le->line[0]), le->cursor_index_for_line );
    fprintf(tty_debug, "CLIPBOARD = |%s|\n", le->clipboard);
}
