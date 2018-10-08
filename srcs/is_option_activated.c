/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_option_activated.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 19:16:07 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/11 19:51:40 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

bool	is_option_activated(char *opt_str, \
			t_option *opt_list, t_option **char_opt_index)
{
	t_option	*opt_ptr;

	opt_ptr = NULL;
	if (opt_str)
	{
		if (*opt_str != '-' && \
			char_opt_index && \
			char_opt_index[(int)*opt_str])
			opt_ptr = char_opt_index[(int)*opt_str];
		else
			opt_ptr = get_opt_elem(opt_list, opt_str);
	}
	return ((opt_ptr) ? (opt_ptr->opt_status) : (false));
}
