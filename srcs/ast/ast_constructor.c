/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_constructor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 09:59:44 by sbrucker          #+#    #+#             */
/*   Updated: 2018/09/20 14:52:39 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static int	put_node(t_lexeme **lex, t_ast **root, t_ast *new, \
			void(* const node_placer)(t_ast *, t_ast *));

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

static int	is_bypass_token(t_ast *node)
{
	int		i;

	i = 0;
	while (g_token_bypass[i])
	{
		if (node->type_details == g_token_bypass[i])
			return (1);
		i++;
	}
	return (0);
}

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

static t_lexeme	*create_sub_ast(t_lexeme *lex, t_ast **root, const size_t next_tokens[],
				void (* const node_placer)(t_ast *, t_ast *))
{
	t_lexeme	*end_lexeme;

	end_lexeme = find_end_lexeme(lex, next_tokens);
	if (!end_lexeme)
		return (NULL);
	lex = lex->next;
	log_debug("lex->data = %s / end_lexeme->data = %s", lex->data, end_lexeme->data);
	if (lex == end_lexeme)
		log_warn("Find end lexeme: end_lexeme is the same than start ! %s - %p", lex->data, lex);
	log_debug("Find end lexeme: lex %s - %p / end_lexeme %s - %p", lex->data, lex, end_lexeme->data, end_lexeme);
	log_debug("BEGIN: Lex : %s - %p / End : %s - %p", lex->data, lex, end_lexeme->data, end_lexeme);
	*root = ast_constructor(&lex, *root, end_lexeme, node_placer);
	log_debug("END: Lex : %s - %p / End : %s - %p", lex->data, lex, end_lexeme->data, end_lexeme);
	return (lex);
}

static t_lexeme	*need_subast(t_lexeme *lex, t_ast **root, t_ast *new, \
				void (* const node_placer)(t_ast *, t_ast *))
{
	int		i;
	t_ast	*node_subast;
	t_lexeme	*save;

	i = 0;
	while (g_tokens[i])
	{
		if (new->type_details == g_tokens[i])
		{
			log_trace("new type details %d", new->type_details);
			node_subast = create_node(T_WORD, TK_SUBAST, debug_data_node("[subast]"));
			node_placer(*root, node_subast);
			*root = node_subast;
			root[0]->sub_ast = create_node(T_CTRL_OPT, TK_SEMICOLON, NULL);
			//log_error("lex->data %s - %p", lex->data, lex);
			save = lex;
			put_node(&save, &(root[0]->sub_ast), new, g_node_placer[i]);
			while (lex && lex->type == T_WORD)
				lex = lex->next;
			//log_error("lex->data %s - %p", lex->data, lex);
			//log_trace("g_next_tokens[%d] = %d", i, g_next_tokens[i]);
			return(create_sub_ast(lex, &(root[0]->sub_ast), g_next_tokens[i], g_node_placer[i]));
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

static int	put_node(t_lexeme **lex, t_ast **root, t_ast *new, \
			void(* const node_placer)(t_ast *, t_ast *))
{
	int		flag_heredoc_EOF;

	flag_heredoc_EOF = manage_heredoc(*lex);
	if (!is_bypass_token(new))
	{
		log_trace("Put_node: %s - %p", new->data[0], new);
		node_placer(*root, new);
		*root = new;
	}
	else
		log_trace("BYPASS Put_node: %s - %p", new->data[0], new);
	if (lex[0]->type == T_WORD && !is_bypass_token(new))
		while (*lex && lex[0]->type == T_WORD)
			*lex = lex[0]->next;
	else
		*lex = lex[0]->next;
	return (flag_heredoc_EOF);
}

int		depth = -1;

t_ast		*ast_constructor(t_lexeme **lex, t_ast *root, t_lexeme *end, \
			void(* const node_placer)(t_ast *, t_ast *))
{
	t_ast	*new;
	t_lexeme	*save;
	int		flag_heredoc_EOF;
	t_ast		*save_root;

	depth++;
	log_info("Construction of new AST. root = %p. Depth = %d", root, depth);
	flag_heredoc_EOF = 0;
	save_root = root;
	while (save_root->parent)
		save_root = save_root->parent;
	while (*lex != end)
	{
		//log_error("lex->data = %s, lex = %p, end = %p", lex[0]->data, *lex, end);
		//ast_debug(save_root);
		//getchar();
		new = create_node(lex[0]->type, lex[0]->type_details, \
				prepare_argv(*lex, flag_heredoc_EOF));
		save = *lex;
		*lex = need_subast(*lex, &root, new, node_placer);
		if (!*lex)
			return (NULL);
		if (*lex != save)
			continue;
		flag_heredoc_EOF = put_node(lex, &root, new, node_placer);
	}
	while (root->parent)
		root = root->parent;
	log_info("End of constructing this AST. - %p. Depth = %d\n \
			lex = %p. end = %p", root, depth, *lex, end);
	depth--;

	return (root);
}
