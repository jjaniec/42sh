/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 14:59:17 by sbrucker          #+#    #+#             */
/*   Updated: 2018/11/30 18:30:08 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

int		prompt_show(const char *prompt)
{
	if (prompt == g_prompts[0])
		print_prompt_details();
	tputs(access_le_main_datas()->tcaps->md, 1, &write_one_char);
	ft_putstr(prompt);
	if (prompt != g_prompts[0])
	{
		ft_putstr(g_prompts[0]);
		ft_putstr(COL_DEFAULT);
	}
	ft_putstr(COL_DEFAULT);
	tputs(access_le_main_datas()->tcaps->me, 1, &write_one_char);
	return ((prompt != g_prompts[0]) ? (ft_strlen(prompt) + 2) : (2));
}

int		subpp_string(char **s)
{
	char	*new;
	char	*input;

	input = RESIZE_IN_PROGRESS;
	while (input == RESIZE_IN_PROGRESS)
	{
		input = line_edition(NEED_SUBPROMPT_QUOTES);
		if (input == NULL)
			return (0);
	}
	ft_putchar('\n');
	new = ft_xstrjoin_free(*s, input);
	*s = new;
	return (1);
}

static void	multiline_merge(t_lexeme *last, t_lexeme *new)
{
	char	*tmp;

	if (!last->lexeme_end_ptr[0] && new->pos == (int)ft_strlen(new->data))
	{
		tmp = ft_xstrdup(last->data);
		free(last->data);
		last->data = ft_xstrjoin_free(tmp, new->data);
		last->next = new->next;
		free(new);
	}
	else
		last->next = new;
}

t_lexeme	*subp_lexeme(t_lexeme *lex, int need_subprompt)
{
	char		*input;
	t_lexeme	*new;
	t_lexeme	*save;

	input = RESIZE_IN_PROGRESS;
	while (input == RESIZE_IN_PROGRESS)
	{
		input = get_valid_input(&new, need_subprompt);
		free_lexemes(new);
		if (input == NULL)
			return (NULL);
	}
	lexer(input, &new, NULL);
	aliases_replace(&new);
	free(input);
	if (!lex)
		return (new);
	save = lex;
	while (lex->next && lex->next->next)
		lex = lex->next;
	if (lex->next && lex->next->type_details == TK_NEWLINE)
	{
		free(lex->next->data);
		free(lex->next);
		lex->next = new;
	}
	else if (lex->next && lex->next->type_details != TK_NEWLINE)
		lex->next->next = new;
	else if (lex->next && !lex->next->next && lex->next->type == T_WORD
	&& new->type == T_WORD)
	{
		lex->next->data = ft_strjoin(lex->next->data, new->data);
		lex->next->next = new->next;
	}
	else if (lex && !lex->next && lex->type == T_WORD && new
	&& new->type == T_WORD)
		multiline_merge(lex, new);
	else if (lex)
		lex->next = new;
	return (save);
}

static int	there_is_no_cr(char *input)
{
	size_t	input_len;

	input_len = ft_strlen(input);
	if (input_len >= 2 && input[input_len - 1] == '\n'
	&& input[input_len - 2] == '\\')
	{
		input[ft_strlen(input) - 2] = '\0';
		return (1);
	}
	return (0);
}

static int	get_full_line(char **final_input)
{
	t_lexeme	*lex;
	char		*input;

	input = get_valid_input(&lex, NEED_SUBPROMPT_HEREDOC);
	free_lexemes(lex);
	if (!input)
		return (0);
	while (there_is_no_cr(input))
	{
		*final_input = ft_xstrjoin_free(*final_input, input);
		input = get_valid_input(&lex, NEED_SUBPROMPT_NEWLINE);
		free_lexemes(lex);
		if (!input)
			return (0);
	}
	*final_input = ft_xstrjoin_free(*final_input, input);
	return (1);
}

int		subp_heredoc(t_lexeme *lex, char *eof_word_tmp)
{
	char	*final_input;
	char	*final;
	char	*eof_word;

	final = ft_xmemalloc(sizeof(char));
	eof_word = ft_xstrjoin(eof_word_tmp, "\n");
	while (1)
	{
		final_input = (char *)ft_xmemalloc(sizeof(char));
		if (!get_full_line(&final_input))
		{
			free(final_input);
			free(final);
			free(eof_word);
			return (0);
		}
		if (ft_strequ(final_input, eof_word))
			break ;
		final = ft_xstrjoin_free(final, final_input);
	}
	free(eof_word);
	free(final_input);
	free(lex->next->data);
	lex->next->data = final;
	return (1);
}
