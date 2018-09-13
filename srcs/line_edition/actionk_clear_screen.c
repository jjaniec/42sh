/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_clear_screen.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 14:34:18 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/13 14:54:32 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void	actionk_clear_screen(struct s_line *le)
{
	// reafficher le prompt de jj qui dit le dir et la branche git la
	// puis afficher le petit prompt %> en fonction duquel c'est 
	// puis reafficher la ligne en cours d'edition

	tputs(le->tcaps->cl, 1, &write_one_char);
}
