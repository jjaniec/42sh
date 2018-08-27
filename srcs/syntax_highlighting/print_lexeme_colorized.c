/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lexeme_colorized.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 07:13:38 by jjaniec           #+#    #+#             */
/*   Updated: 2018/08/27 18:51:27 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Print color associated w/ type of element found in string
*/

static void		print_prog_name_arg(struct stat *elem_stats, int elem_found, int item_nb)
{
	if (elem_found)
	{
		if (item_nb == 0)
			ft_putstr(COL_PROG_NAME_FOUND);
		else
		{
			if (S_ISDIR(elem_stats->st_mode))
				ft_putstr(COL_PROG_ARG_DIR);
			else
				ft_putstr(COL_PROG_ARG_FILE);
		}
	}
	else
	{
		if (item_nb == 0)
			ft_putstr(COL_PROG_NAME_NOT_FOUND);
		else
			ft_putstr(COL_PROG_ARG_NOT_FOUND);
	}
}

static void		put_lexeme_color(t_lexeme *lexeme, char *lexeme_begin, char **env)
{
	struct stat		elem_stats;
	static int		item_nb = -1;

	item_nb++;
	if (lexeme->type == T_CTRL_OPT)
	{
		ft_putstr(COL_OPERATORS);
		item_nb = -1;
	}
	else if (lexeme->type == T_REDIR_OPT)
		ft_putstr(COL_REDIRS);
	else if (lexeme->type == T_WORD)
	{
		if (*(char *)(lexeme->data) == '-')
			ft_putstr(COL_PROG_OPT);
		else if (*(lexeme_begin) == '$')
			ft_putstr(COL_ENV_VAR_EXPANSION);
		else if (*(lexeme_begin) == '\'' || *(lexeme_begin) == '"')
			ft_putstr(COL_QUOTED_ARG);
		else
		{
			print_prog_name_arg(&elem_stats, \
				elem_path_found(&elem_stats, lexeme->data, env, item_nb), item_nb);
		}
	}
}

void			print_lexeme_colorized(char *lexeme_begin, char *lexeme_end, char *input_ptr, t_lexeme *lexeme, char **envp)
{
	(void)lexeme_end;
	put_lexeme_color(lexeme, lexeme_begin, envp);
	write(1, input_ptr, (lexeme_end - input_ptr));
	ft_putstr(COL_DEFAULT);
}