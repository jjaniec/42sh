/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expansions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 16:01:23 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/18 19:36:45 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static char		*get_expansion_end(char *str, char *lexeme_end_ptr)
{
	char		*r;

	r = str + 1;
	while (*r && *r != '$' && r != lexeme_end_ptr)
		r++;
	log_fatal("exp end *%s", r);
	return (r);
}

static char		*concat_expansion(t_lexeme *lexeme, char *expansion_char_pos, \
					char *expansion_data, char *env_val)
{
	//char	*expansion_end;
	char	*expansion_prefix_data;
	char	*expansion_suffix_data;
	char	*ret;
	char	*ptr;
	int		i;
(void)expansion_data;
	expansion_prefix_data = lexeme->data;
	log_debug("exp prefix data %s", expansion_prefix_data);
	expansion_suffix_data = get_expansion_end(expansion_char_pos, lexeme->lexeme_end_ptr);
	log_debug("exp suffix data %s", expansion_suffix_data);

	ret = malloc(sizeof(char) * ft_strlen(lexeme->data) - ft_strlen(expansion_char_pos) + ft_strlen(env_val) + 1);
	ptr = expansion_prefix_data;
	i = 0;
	log_info("exp char pos : %s", expansion_char_pos);
	while (ptr && *ptr && *ptr != *expansion_char_pos)
		ret[i++] = *(ptr++);
	log_info("Stop 1st while %s", ret);
	while (env_val && *env_val)
		ret[i++] = *(env_val++);
	ptr = expansion_suffix_data;
	while (ptr && *ptr)
		ret[i++] = *(ptr++);
	ret[i] = '\0';
	return (ret);
}

static void		handle_dollar_expansion(t_lexeme *lexeme, char *expansion_char_pos, char **env)
{
	char		*new_data;
	char		exp_end_char;
	char		*env_val;
	char		*exp_end;

	log_fatal("Expansion char pos : |%s| end |%s|", expansion_char_pos, lexeme->lexeme_end_ptr);

	exp_end = get_expansion_end(expansion_char_pos, lexeme->lexeme_end_ptr); //*(lexeme->lexeme_end_ptr);
	exp_end_char = *(exp_end);
	*(exp_end) = '\0';
	env_val = get_env(expansion_char_pos + 1, (const char **)env);
	if (env_val)
	{
		new_data = ft_strdup(env_val);
		if (lexeme->lexeme_begin_ptr != expansion_char_pos)
			new_data = concat_expansion(lexeme, expansion_char_pos, new_data, env_val);
	}
	else
	{/*
		if (lexeme->next)
		{
			if (lexeme->prev)
				lexeme->next->prev = lexeme->prev;
			else
				lexeme->next->prev = NULL;
		}*/
/*
		if (lexeme->lexeme_begin_ptr != expansion_char_pos)
			new_data = concat_expansion(lexeme, new_data);*/
		new_data = ft_strdup("");
	}
	free(lexeme->data);
	lexeme->data = new_data;
	*(exp_end) = exp_end_char;
	log_info("lexeme data replaced w/ : %s", lexeme->data);
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
			log_fatal("handle exp of : |%s|, lexeme->begin[0] |%c|", lexeme->lexeme_begin_ptr + i, lexeme->lexeme_begin_ptr[i]);

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
