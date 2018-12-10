/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_constructor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 09:59:44 by sbrucker          #+#    #+#             */
/*   Updated: 2018/12/10 19:31:09 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

t_ast		*ast_constructor(t_lexeme **lex, t_ast *root, t_lexeme *end, \
			void(*const node_placer)(t_ast *, t_ast *))
{
	t_ast		*new;
	t_lexeme	*save;
	int			flag_heredoc_eof;
	t_ast		*save_root;

	flag_heredoc_eof = 0;
	save_root = root;
	while (save_root->parent)
		save_root = save_root->parent;
	while (*lex != end)
	{
		new = create_node(lex[0]->type, lex[0]->type_details, \
				prepare_argv(*lex, flag_heredoc_eof));
		save = *lex;
		*lex = need_subast(*lex, &root, new, node_placer);
		if (!*lex)
			return (NULL);
		if (*lex == save)
			flag_heredoc_eof = put_node(lex, &root, new, node_placer);
	}
	while (root->parent)
		root = root->parent;
	return (root);
}
