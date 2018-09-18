/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expansions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 16:01:23 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/18 17:36:44 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static void		handle_dollar_expansion(t_lexeme *lexeme, char *expansion_char_pos, char **env)
{
	char		*new_data;
	char		lexeme_end_char;
	char		*env_val;

	log_fatal("Expansion char pos : |%s| end |%s|", expansion_char_pos, lexeme->lexeme_end_ptr);

	lexeme_end_char = *(lexeme->lexeme_end_ptr);
	*(lexeme->lexeme_end_ptr) = '\0';
	env_val = get_env(expansion_char_pos + 1, (const char **)env);
	if (env_val)
		new_data = ft_strdup(env_val);
	else
		new_data = ft_strdup("");
	free(lexeme->data);
	lexeme->data = new_data;
	*(lexeme->lexeme_end_ptr) = lexeme_end_char;
}

static int		is_expansion_char(char c, void **callback)
{
	*callback = NULL;
	if (c == '$')
		*callback = handle_dollar_expansion;
	/*
	else if (c == '~')
		*callback = handle_tild_expansion;*/
	return ((*callback) ? (1) : (0));
}

static void		handle_lexeme_expansions(t_lexeme *lexeme, char **env)
{
	int		i;
	void	*expansion_handler;
	int		in_quote_type;

	i = 0;
	in_quote_type = NOT_IN_QUOTES;
	log_fatal("handle exp of : |%s|, lexeme->begin[0] |%c|", lexeme->data, lexeme->lexeme_begin_ptr[i]);
	while (lexeme->lexeme_begin_ptr[i] && \
		(lexeme->lexeme_begin_ptr + i) != lexeme->lexeme_end_ptr)
	{
		if (lexeme->lexeme_begin_ptr[i] == '\\')
		{
			handle_backslash_escape(\
				lexeme->lexeme_begin_ptr, &i, in_quote_type);
			log_debug("End of backslash escape : |%s|", lexeme->lexeme_begin_ptr + i);
		}
		else if (is_expansion_char(lexeme->lexeme_begin_ptr[i], &expansion_handler))
		{
			(*(void (*)(t_lexeme *, char *, char **))(expansion_handler))\
				(lexeme, lexeme->lexeme_begin_ptr + i, env);
		}
		i++;
	}
}

void			handle_expansions(char *input, t_lexeme *lexemes, char **env)
{
	t_lexeme	*cur_lexeme;

	(void)input;
	cur_lexeme = lexemes;
	while (cur_lexeme)
	{
		log_trace("Current lex data : %s t %zu td %zu", cur_lexeme->data, cur_lexeme->type, cur_lexeme->type_details);
		if (cur_lexeme->type == T_WORD && cur_lexeme->type_details == TK_DEFAULT)
			handle_lexeme_expansions(cur_lexeme, env);
		cur_lexeme = cur_lexeme->next;
	}
}
