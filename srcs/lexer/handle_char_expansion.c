/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_char_expansion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 16:38:44 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/19 20:16:58 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void		handle_dollar_expansion(char *exp_char_ptr, char **env, char **s_ptr, char **i_ptr)
{
	(void)exp_char_ptr;
	(void)env;
	(void)s_ptr;
	(void)i_ptr;
	log_trace("MDR: %s", exp_char_ptr);

	*i_ptr += 1;
}
