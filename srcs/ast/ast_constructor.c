/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_constructor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 09:59:44 by sbrucker          #+#    #+#             */
/*   Updated: 2018/09/10 17:01:27 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

const size_t	g_token_bypass[] = {
	TK_SCRIPT_THEN,
	TK_SCRIPT_ELSE,
	TK_SCRIPT_FI,
	TK_SCRIPT_DO,
	TK_SCRIPT_DONE,
	0
};
const size_t	g_tokens[] = {
	TK_SCRIPT_IF,
	TK_SCRIPT_THEN,
	TK_SCRIPT_ELSE,
	TK_SCRIPT_WHILE,
	TK_SCRIPT_DO,
	TK_SCRIPT_CONDITION_IF,
	TK_SCRIPT_CONDITION_WHILE,
	0
};
const size_t	g_next_tokens[][4] = {
	{TK_SCRIPT_FI, 0, 0, 0},
	{TK_SCRIPT_ELIF, TK_SCRIPT_ELSE, TK_SCRIPT_FI, 0},
	{TK_SCRIPT_FI, 0, 0, 0},
	{TK_SCRIPT_DONE, 0, 0, 0},
	{TK_SCRIPT_DONE, 0, 0, 0},
	{TK_SCRIPT_THEN, 0, 0, 0},
	{TK_SCRIPT_DO, 0, 0, 0},
};
void	(* const g_node_placer[])(t_ast *, t_ast *) = {
	&node_placer_if,
	&node_placer_classic,
	&node_placer_classic,
	&node_placer_while,
	&node_placer_classic,
	&node_placer_classic,
	&node_placer_classic
};

static char	**debug_data_node(char *str)
{
	char	**tab_;

	tab_ = (char **)malloc(sizeof(char *) * 2);
	if (!tab_)
		exit(MALLOC_ERROR);
	tab_[0] = str;
	tab_[1] = NULL;
	return (tab_);
}

static t_lexeme	*create_sub_ast(t_lexeme *lex, t_ast *root, const size_t next_tokens[],
				void (* const node_placer)(t_ast *, t_ast *))
{
	t_lexeme	*end_lexeme;

	end_lexeme = find_end_lexeme(lex, next_tokens);
	if (lex == end_lexeme)
		log_warn("Find end lexeme: end_lexeme is the same than start ! %s - %p", lex->data, lex);
	ast_constructor(lex->next, root, end_lexeme, node_placer);
	return (end_lexeme);
}

static t_lexeme	*need_subast(t_lexeme *lex, t_ast **root, t_ast *new, \
				void (* const node_placer)(t_ast *, t_ast *))
{
	int		i;
	t_ast	*node_subast;

	i = 0;
	while (g_tokens[i])
	{
		if (new->type_details == g_tokens[i])
		{
			node_subast = create_node(T_WORD, TK_DEFAULT, debug_data_node("[subast]"));
			node_placer(*root, node_subast);
			*root = node_subast;
			root[0]->sub_ast = create_node(T_CTRL_OPT, TK_SEMICOLON, NULL);
			g_node_placer[i](root[0]->sub_ast, new);
			return(create_sub_ast(lex, new, g_next_tokens[i], g_node_placer[i]));
		}
		i++;
	}
	return (lex);
}

static int	manage_heredoc(t_lexeme *lex)
{
	if (lex->type_details == TK_DLESS)
	{
		log_debug("Hey heredoc here on lex->data %s", lex->data);
		subp_heredoc(lex, lex->next->data);
		return (1);
	}
	return (0);
}

static int	is_bypass_token(t_ast *node)
{
	int		i;

	i = 0;
	while (g_token_bypass[i])
	{
		if (node->type_details == g_token_bypass[i])
		{
			log_info("Bypass this token: %s - %zd", node->data[0],  g_token_bypass[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

t_ast		*ast_constructor(t_lexeme *lex, t_ast *root, t_lexeme *end, \
			void(* const node_placer)(t_ast *, t_ast *))
{
	t_ast	*new;
	int		flag_heredoc_EOF = 0;
	t_lexeme	*save;

	log_info("Construction of new AST. root = %p", root);
	while (lex != end)
	{
		new = create_node(lex->type, lex->type_details, \
				prepare_argv(lex, flag_heredoc_EOF));
		save = lex;
		lex = need_subast(lex, &root, new, node_placer);
		if (lex != save)
			continue;
		flag_heredoc_EOF = manage_heredoc(lex);
		if (!is_bypass_token(new))
		{
			node_placer(root, new);
			root = new;
		}
		if (lex->type == T_WORD)
			while (lex && lex->type == T_WORD)
				lex = lex->next;
		else
			lex = lex->next;
	}
	while (root->parent)
		root = root->parent;
	log_info("End of constructing this AST.");
	return (root);
}
