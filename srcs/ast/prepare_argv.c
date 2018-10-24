/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_argv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 15:52:17 by jjaniec           #+#    #+#             */
/*   Updated: 2018/10/19 16:55:46 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** If pointed lexeme is an operator, only store lexeme data as argv
*/

static char		**prepare_argv_operator(t_lexeme *lexemes)
{
	char		**argv;

	argv = (char **)ft_xmemalloc(sizeof(char *) * 2);
	argv[0] = ft_xstrdup(lexemes->data);
	argv[1] = NULL;
	return (argv);
}

/*
** Return 1 if passed lexeme should be passed as program argument
*/

static int		should_add_to_argv(t_lexeme *ptr)
{
	if ((ptr->type != T_CTRL_OPT) && ptr->type_details != TK_PIPE)
		return (1);
	return (0);
}

/*
** Count number of elements found in the lexeme linked list
** to add as program argument
*/

static int		count_argv(t_lexeme *lexemes)
{
	t_lexeme	*ptr;
	int			r;

	ptr = lexemes;
	r = 1;
	while (ptr && should_add_to_argv(ptr))
	{
		if (ptr->type == T_WORD)
			r += 1;
		ptr = ptr->next;
	}
	return (r);
}

/*
** Fill $argv pointers tab containing command arguments
*/

static char		**fill_argv_tab(char ***argv, t_lexeme *lexemes)
{
	t_lexeme	*ptr;
	int			i;

	ptr = lexemes;
	i = 0;
	while (ptr && should_add_to_argv(ptr))
	{
		if (ptr->type == T_WORD)
			(*argv)[i++] = ft_xstrdup(ptr->data);
		if (ptr->type == T_REDIR_OPT)
			ptr = ptr->next;
		if (ptr)
			ptr = ptr->next;
	}
	(*argv)[i] = NULL;
	return (*argv);
}

/*
** Creates a char pointer tab with each pointer
** containing an argument of the current command to be passed to execve()
*/

char			**prepare_argv(t_lexeme *lexemes, int flag_heredoc_eof)
{
	char	**argv;

	if (lexemes->type == T_SCRIPT_CONDITION)
	{
		log_info("This is a condition !");
		lexemes->type = T_WORD;
		argv = ft_xmalloc(sizeof(char *) * (count_argv(lexemes) + 1));
		return (fill_argv_tab(&argv, lexemes));
	}
	if (lexemes->type != T_WORD || flag_heredoc_eof)
		return (prepare_argv_operator(lexemes));
	argv = ft_xmalloc(sizeof(char *) * (count_argv(lexemes) + 1));
	return (fill_argv_tab(&argv, lexemes));
}
