/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_is_at_end_of_term_line.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:51:54 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/02 20:52:08 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

bool	cursor_is_at_end_of_term_line(unsigned int cursorpos, struct s_line *le)
{
	if (cursorpos == (le->term_line_size - 1))
		return (true);
	return (false);
}
