/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_input_string_end.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 18:33:03 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/13 14:25:55 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

void		print_input_string_end(char *ptr, char *unmatched_quote_err_ptr)
{
	struct s_line	*le;

		le = access_le_main_datas();

	if (ptr && *ptr)
	{
		if (unmatched_quote_err_ptr)
			ft_putstr(COL_QUOTED_ARG);
		le = access_le_main_datas();
		while (*ptr)
			print_key_at_end(le, *ptr++);
		ft_putstr(COL_DEFAULT);
	}
}