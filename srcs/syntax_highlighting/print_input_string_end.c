/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_input_string_end.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 18:33:03 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/06 18:09:52 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void		print_input_string_end(char *ptr, char *unmatched_quote_err_ptr)
{
	struct s_line	*le;

	if (ptr && *ptr)
	{
		if (unmatched_quote_err_ptr)
			ft_putstr(COL_QUOTED_ARG);
		else
			return ;
		le = access_le_main_datas();
		while (*ptr)
			print_key_at_end(le, *ptr++);
		ft_putstr(COL_DEFAULT);
	}
}