/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str_on_term.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 21:18:37 by cfermier          #+#    #+#             */
/*   Updated: 2018/08/20 16:11:33 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

unsigned int	print_str_on_term(const char *str,
								  unsigned int tmp_current_cursor_pos,
								  struct s_line *le, int foo)
{
fprintf(tty_debug, "TERFOO = %d\n", foo);

    bool foofoo = false;
    if (foo == LE_SPECIAL_CASE)
    {
        foo = 2;
        foofoo = true;
    }

    while (*str != '\0')
    {
        ++tmp_current_cursor_pos;
       // fprintf(tty_debug, "IFFFFFF %u\n", tmp_current_cursor_pos - foo );
        if (tmp_current_cursor_pos - foo == le->term_line_size - 1)
        {

fprintf(tty_debug, "- - - - - - TERPRINT DOWN\n");

            tputs(le->tcaps->_do, 1, &write_one_char);
            cursor_crosses_screen(le, CROSS_TO_LEFT);
            tmp_current_cursor_pos = 0;

            if (foofoo == true)
            {
                foo = 1;
                foofoo = false;
            }
        }

        print_key(*str);

fprintf(tty_debug, "- - - - - - TERPRINT |%c|\n", *str);

        ++str;
    }
	return (tmp_current_cursor_pos);
}
