/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 14:59:17 by sbrucker          #+#    #+#             */
/*   Updated: 2018/09/19 15:36:06 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

int		prompt_show(const char *prompt)
{
	tputs(tgetstr("md", NULL), 1, &write_one_char);
	ft_putstr(prompt);
	if (prompt != g_prompts[0])
		ft_putstr(g_prompts[0]);
	tputs(tgetstr("me", NULL), 1, &write_one_char);
	return (ft_strlen(prompt) + ft_strlen(g_prompts[0]));
}

void	subp_string(char **s)
{
	char	*new;
	char	*input;
	int			prompt_size;

	prompt_size = prompt_show(g_prompts[-NEED_SUBPROMPT_QUOTES]);
	input = line_edition(prompt_size);
	ft_putchar('\n');
	new = ft_strjoin(*s, input);
	*s = new;
}

t_lexeme	*subp_lexeme(t_lexeme *lex, int need_subprompt)
{
	char		*input;
	t_lexeme	*new;
	t_lexeme	*save;
	int			prompt_size;

	prompt_size = prompt_show(g_prompts[-need_subprompt]);
	input = line_edition(prompt_size);
	ft_putchar('\n');
	lexer(input, &new, NULL);
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
	{
		lex->next->next = new;
	}
	else if (lex->next && !lex->next->next && lex->next->type == T_WORD && new->type == T_WORD)
	{
		lex->next->data = ft_strjoin(lex->next->data, new->data);
		lex->next->next = new->next;
	}
	else if (lex && !lex->next && lex->type == T_WORD && new && new->type == T_WORD)
	{
		lex->data = ft_strjoin(lex->data, new->data);
		lex->next = new->next;
	}
	else if (lex)
		lex->next = new;
	return (save);
}

static int	there_is_no_cr(const char *input)
{
	if (ft_strlen(input) >= 2 && input[ft_strlen(input) - 1] == '\n' && input[ft_strlen(input) - 2] == '\\')
		return (1);
	return (0);
}

void	subp_heredoc(t_lexeme *lex, char *eof_word)
{
	char	*input;
	char	*final_input;
	char	*final;
	int		prompt_size;

	input = NULL;
	final = (char *)ft_memalloc(sizeof(char));
	final_input = (char *)ft_memalloc(sizeof(char));
	if (!final || !final_input)
		exit(MALLOC_ERROR);
	eof_word = ft_strjoin(eof_word, "\n");
	while (!input)
	{
		prompt_size = prompt_show(g_prompts[-NEED_SUBPROMPT_HEREDOC]);
		input = line_edition(prompt_size);
		ft_putchar('\n');
		final_input = ft_strjoin(final_input, input);
		while (there_is_no_cr(input))
		{
			final_input[ft_strlen(final_input) - 2] = '\0';
			prompt_size = prompt_show(g_prompts[-NEED_SUBPROMPT_NEWLINE]);
			input = line_edition(prompt_size);
			ft_putchar('\n');
			final_input = ft_strjoin(final_input, input);
		}
		if (ft_strequ(final_input, eof_word))
			break ;
		final = ft_strjoin(final, final_input);
		final_input[0] = '\0';
		free(input);
		input = NULL;
	}
	//final[ft_strlen(final) - 1] = '\0';
	lex->next->data = final;
}
