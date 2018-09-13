/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lexeme_colorized.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 07:13:38 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/13 14:50:07 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

//extern struct s_line *g_le;

/*
** Returns 1 if file in lexeme_data was found by searching directories in
** $PATH or if path in lexeme_data exists,
** and store stat of file in elem_stats,
** otherwise return 0
*/

static int		elem_path_found(struct stat *elem_stats, \
					char *lexeme_data, char **env, int item_nb)
{
	char		**paths;
	char		*tmp;

	if (ft_strchr(lexeme_data, '/') || item_nb > 0)
	{
		if (lstat(lexeme_data, elem_stats) != -1)
			return (1);
		return (0);
	}
	else
	{
		paths = get_path(get_env("PATH", (const char**)env));
		if ((tmp = isin_path(paths, lexeme_data)))
		{
			lstat(tmp, elem_stats);
			return (1);
		}
		ft_strdel(&tmp);
	}
	return (0);
}

/*
** Print color associated w/ stats of program argument
** (directory / file / not found)
*/

static void		print_prog_name_arg_col(struct stat *elem_stats, \
					int elem_found, int item_nb)
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

/*
** Prints color associated w/ type of current element
*/

static void		put_lexeme_color(t_lexeme *lexeme, char *lexeme_begin, \
					char **env)
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
			print_prog_name_arg_col(&elem_stats, \
			elem_path_found(&elem_stats, lexeme->data, env, item_nb), item_nb);
	}
	if (!lexeme->next)
		item_nb = -1;
}

/*
** Print color associated w/ current lexeme w/ put_lexeme_color()
** and reset colors to COL_DEFAULT
*/

void f(const char *s, int nb)
{
	struct s_line *le;

	le = access_le_main_datas();
	while (nb > 0)
	{
		print_key_at_end(le, *s++);
		--nb;
	}
}


void			print_lexeme_colorized(char *lexeme_begin, char *lexeme_end, \
					char *input_ptr, t_lexeme *lexeme, char **envp)
{
	//write(2, "JJANIEC LOL", 11);

	(void)lexeme_end;
	put_lexeme_color(lexeme, lexeme_begin, envp);
//	write(1, input_ptr, (lexeme_end - input_ptr));
	f(input_ptr, (lexeme_end - input_ptr));

	ft_putstr(COL_DEFAULT);
}
