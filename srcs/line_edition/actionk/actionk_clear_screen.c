/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_clear_screen.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 14:34:18 by cyfermie          #+#    #+#             */
/*   Updated: 2018/10/14 19:58:38 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

//  NOT FINISHED YET

/*
**	Clear the entire window then redraw the prompt and the line being edited.
*/

void	actionk_clear_screen(struct s_line *le)
{
	// reafficher le prompt de jj qui dit le dir et la branche git la
	// puis afficher le petit prompt %> en fonction duquel c'est 
	// puis reafficher la ligne en cours d'edition

	tputs(le->tcaps->cl, 1, &write_one_char);

	prompt_show( g_prompts[ -(le->le_state.prompt_type) ] );
	print_str_on_term(le->cmd, /*le->start_pos*/ 0 , le, 0);
}
