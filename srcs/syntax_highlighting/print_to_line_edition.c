/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_to_line_edition.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 18:40:35 by sbrucker          #+#    #+#             */
/*   Updated: 2018/12/06 18:40:51 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void			print_to_line_edition(const char *s, int nb)
{
	struct s_line *le;

	le = access_le_main_datas();
	while (nb > 0)
	{
		print_key_at_end(le, *s++);
		--nb;
	}
}
