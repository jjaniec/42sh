/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 16:28:40 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/02 20:15:48 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

extern char **g_envp;

static bool	key_is_printable(t_kno key)
{
	if (key >= 32 && key <= 126)
		return (true);
	return (false);
}

void	process_key(t_kno key, struct s_line *le)
{
	t_lexeme	*lexemes;
	char		*unmatched_quote_err_ptr;

	le->key_no = key;
	if (key_is_printable(key) == true)
	{
		char tmp[LE_LINE_SIZE] = {0};

		ft_strcpy(tmp, le->line);
		tmp[le->line_index] = key;
		fprintf(tty_debug, "MDR TMP c |%s|\n", tmp);
		lexer(tmp, &lexemes, &unmatched_quote_err_ptr);
	//	fprintf(tty_debug, "MDR elem begin [0] c |%s| |%s|\n", lexemes->lexeme_begin_ptr, lexemes->lexeme_end_ptr);


	//	char *tmp = strdup("ls -la lolmdr ..");

//		actionk_delete_current_input(le);
		fprintf(tty_debug, "PTDR line c |%s|\n", le->line);
		if (!ft_strchr(LE_IFS, key))
		{
			actionk_delete_current_input(le);

			print_colorized_input(tmp, g_envp, lexemes, unmatched_quote_err_ptr);
		}
		else
			print_key_at_end(le, key);

		/*
		if ( cursor_is_at_end_of_cmd(le) == true )
		{
			print_key_at_end(le, key);
		}
		else
		{
			insert_character_into_cmdline(le, key);
		}
		*/
	}

	else if (key == '\n')
	{
		le->line[le->line_index] = key;
		// check depassement tableau
	}
	else
	{
		action_key(key, le);
	}
}
