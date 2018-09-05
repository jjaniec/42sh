/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 16:28:40 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/05 16:10:01 by jjaniec          ###   ########.fr       */
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
/*
void	handle_quote_subprompts(t_lexeme **lexemes, char end_subprompt_char, char *str)
{
	t_lexeme	*subprompt_lexemes;
	char		*unmatched_quote_err_ptr;

	lexemes
}*/

void	process_key(t_kno key, struct s_line *le)
{
	t_lexeme	*lexemes;
	char		*unmatched_quote_err_ptr;

	lexemes = NULL;
	unmatched_quote_err_ptr = NULL;
	le->key_no = key;
	if (key_is_printable(key) == true)
	{
		if (le->prompt_type == PROMPT_DEFAULT && !ft_strchr(LE_IFS, key))
		{
			char tmp[LE_LINE_SIZE] = {0};

			ft_strcpy(tmp, le->line);
			tmp[le->line_index] = key;
			fprintf(tty_debug, "tmp: |%s|\n", tmp);
			lexer(tmp, &lexemes, &unmatched_quote_err_ptr);
			actionk_delete_current_input(le);
			print_colorized_input(tmp, g_envp, lexemes, \
				unmatched_quote_err_ptr);
			fprintf(tty_debug, "concat string : %s\n", tmp);
		}
		else
		{
			//fprintf(tty_debug, "concat string : %s\n", tmp);
			print_key_at_end(le, key);
		}

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
	}

//		if (le->prompt_type == PROMPT_DEFAULT && unmatched_quote_err_ptr)
			
	/*	if (unmatched_quote_err_ptr)
			handle_quote_subprompts(&lexemes, *unmatched_quote_err_ptr);*/
		// check depassement tableau
	//}
	else
	{
		action_key(key, le);
	}
}
