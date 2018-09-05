/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_char_into_array.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 17:53:09 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/05 18:12:34 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void	insert_char_into_array(char *line, t_kno key, unsigned int pos)
{
	// check depassement tableau

	//fprintf(tty_debug, "BEFORE LINE = |%s|\n", line);

	//fprintf(tty_debug, "je bouge |%s|\n",   line + pos );

	ft_memmove(line + pos + 1, line + pos, ft_strlen(line + pos) );

	line[pos] = key;

	//fprintf(tty_debug, "AFTER LINE  = |%s|\n", line);
}
