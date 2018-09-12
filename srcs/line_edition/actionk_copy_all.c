/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_copy_all.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 16:50:52 by cfermier          #+#    #+#             */
/*   Updated: 2018/09/02 20:51:58 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void	actionk_copy_all(struct s_line *le)
{
    le->clipboard_len = 0;

 	check_clipboard_storage(le, le->line_index);

    ft_strcpy(le->clipboard, le->line);
    le->clipboard_len = le->line_index;
	fprintf(tty_debug, "CLIPBOARD = |%s|\n", le->clipboard);
}
