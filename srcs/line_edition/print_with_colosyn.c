/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_with_colosyn.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 19:39:07 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/05 18:46:57 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

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

	if (le->prompt_type == PROMPT_DEFAULT && ft_strchr(LE_IFS, key) == NULL)
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
