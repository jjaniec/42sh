/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_with_colosyn.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 19:39:07 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/06 21:31:54 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// CE FICHIER SERA SUPPRIME CAR LA PREMIERE FONCTION C JJ QUI L'A ET
// LA SECONDE EST UNE ANCIENNE VERSION PLUS UTILISEE

#include <twenty_one_sh.h>

void		refresh_colorized_printing(struct s_line *le, char *cmd)
{
	t_lexeme	*lexemes;
	char		*unmatched_quote_err_ptr;

	fprintf(tty_debug, "UPDATED |%s|\n", cmd);

	lexer(cmd, &lexemes, &unmatched_quote_err_ptr);
	//fprintf(tty_debug, "LO<DRdadawdawdwada |%s|\n", cmd);
	actionk_delete_current_input(le);
	//fprintf(tty_debug, "LO<DRwwwwwwwww |%s|\n", cmd);
	print_colorized_input(cmd, g_envp, lexemes, unmatched_quote_err_ptr);

	//fprintf(tty_debug, "LO<DR |%s|\n", cmd);

}
/*
void		print_with_colosyn(struct s_line *le, t_kno key)
{
	char			tmp_array[LE_LINE_SIZE]; // a changer si on use malloc au lieu d'un tab
	unsigned int	keep_cursor_index_for_line;
	bool			need_replace_cursor;
	t_lexeme		*lexemes;
	char			*unmatched_quote_err_ptr;

	ft_memset(tmp_array, '\0', LE_LINE_SIZE);
	keep_cursor_index_for_line = le->cursor_index_for_line;
	need_replace_cursor = false;

	ft_strcpy(tmp_array, le->line);

	if ( cursor_is_at_end_of_cmd(le) == true )
		tmp_array[le->line_index] = key;
	else
	{
		insert_char_into_array(tmp_array, key, le->cursor_index_for_line);
		need_replace_cursor = true;
	}

	fprintf(tty_debug, "MDR TMP_ARRAY c |%s|\n", tmp_array);

	if (le->le_state.prompt_type == PROMPT_DEFAULT && ft_strchr(LE_IFS, key) == NULL)
	{
		lexer(tmp_array, &lexemes, &unmatched_quote_err_ptr);
		actionk_delete_current_input(le);
		print_colorized_input(tmp_array, g_envp, lexemes, \
			unmatched_quote_err_ptr);
		//fprintf(tty_debug, "concat string : %s\n", tmp);
		if (need_replace_cursor == true)
			while (le->cursor_index_for_line > keep_cursor_index_for_line + 1)
				actionk_cursor_move_left(le);
	}
	else
		print_key_at_end(le, key);

}
*/
