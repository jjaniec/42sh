/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   twenty_one_sh.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 18:55:19 by cyfermie          #+#    #+#             */
/*   Updated: 2018/12/10 21:14:44 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

int		twenty_one_sh(char *input, t_shell_vars *vars)
{
	t_ast		*ast_root;
	t_exec		*exe;
	t_lexeme	*lexemes;

	lexemes = NULL;
	if (lexer(input, &lexemes, NULL) == UNMATCHED_QUOTE_ERR)
	{
		ft_putstr_fd("Non-interactive mode: unmatched quote error, exit\n", 2);
		free(input);
		free_lexemes(lexemes);
		exit(EXIT_FAILURE);
	}
	ast_root = ast(&lexemes);
	free(input);
	free_lexemes(lexemes);
	if (!ast_root)
		return (-1);
	link_ast_data(ast_root);
	exe = create_exec(vars->env);
	exe = exec_cmd(ast_root, exe);
	ast_free(ast_root);
	vars->last_cmd_return = exe->ret;
	free_exec(&exe);
	free_job(g_jobs);
	return ((g_jobs = NULL) ? (0) : (0));
}
