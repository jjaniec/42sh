/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autoc_push_in_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 17:02:20 by cgaspart          #+#    #+#             */
/*   Updated: 2018/09/19 17:02:22 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void	autoc_push_in_line(struct s_line *le, char *str, char *search)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (search)
		{
			if (str[i] != search[i])
				insert_and_print_character_into_cmdline(le, (uint64_t)str[i]);
		}
		else
			insert_and_print_character_into_cmdline(le, (uint64_t)str[i]);
		i++;
	}
}
