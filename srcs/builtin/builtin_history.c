/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 19:08:07 by cyfermie          #+#    #+#             */
/*   Updated: 2018/10/16 19:44:08 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**	Return he number of elements in the history.
*/
/*
static unsigned int	get_nb_elem_in_history(void)
{
	struct s_history	*his;
	unsigned int		nb_elem;

	his = access_le_main_datas()->history;
	while (his->prev != NULL)
		his = his->prev;
	nb_elem = 0;
	while (his->cmd != NULL)
	{
		++nb_elem;
		his = his->next;
	}
	return (nb_elem);
}
*/
/*
**	Print all history's elements with an index.
*/

static void	print_history_with_indexes(void)
{
	const struct s_history	*his = access_le_main_datas()->history;
	unsigned int			index;

	index = 1;
	if (his != NULL)
	{
		while (his->prev != NULL)
			his = his->prev;
		while (his->next != NULL)
		{
			ft_putnbr(index);
			if (index < 10)
				write(STDOUT_FILENO, "    ", sizeof(char) * 4);
			else if (index < 100)
				write(STDOUT_FILENO, "   ", sizeof(char) * 3);
			else if (index < 1000)
				write(STDOUT_FILENO, "  ", sizeof(char) * 2);
			else if (index < 10000)
				write(STDOUT_FILENO, " ", sizeof(char) * 1);
			ft_printf("%s\n", his->cmd);
			his = his->next;
			++index;
		}
	}
}

/*
**	Delete element number 'n' in the history list.
*/

static void		delete_element_number_n(unsigned int n)
{
	struct s_history	*his;
	struct s_history	*del;
	unsigned int		index;

	if (n == 0 || (his = access_le_main_datas()->history) == NULL)
		return ;
	while (his->prev != NULL)
		his = his->prev;
	index = 1;
	while (index < n)
	{
		his = his->next;
		++index;
		if (his == NULL)
			return ;
	}
	if (his->cmd == NULL)
		return ;
	del = his;
	if (access_le_main_datas()->history == del)
		reset_history_on_first_elem(access_le_main_datas());
	if (his->prev != NULL)
		his->prev->next = his->next;
	his->next->prev = his->prev;
	free(del->cmd);
	free(del);
}

/*
**	Replace the previous saved history with the current one.
**	The history is saved into a file.
**	Return 'false' if an error occurs.
*/

static bool		save_history_in_file(struct s_history *his)
{
	int		fd;

	if (check_backup_file(get_parsed_history_file_path()) == false)
		return (false);
	if (his == NULL)
		return (true);
	while (his->prev != NULL)
		his = his->prev;
	if ((fd = open(get_parsed_history_file_path(), O_WRONLY | O_TRUNC)) == -1)
	{
		ft_putstr_fd("42sh: error with file .42sh_history\n", STDERR_FILENO);
		return (false);
	}
	while (his->cmd != NULL)
	{
		if (write(fd, his->cmd, ft_strlen(his->cmd)) == (ssize_t)(-1)
		|| write(fd, "\n", sizeof(char)) == (ssize_t)(-1))
		{
			ft_putstr_fd(".42sh_history: error writing in file\n", 2);
			return (close(fd) ? (false) : (false));
		}
		his = his->next;
	}
	close(fd);
	return (true);
}

/*
**	Empty the history list (not the file).
*/

static void	clear_history(struct s_line *le)
{
	struct s_history	*his;
	struct s_history	*del;

	his = le->history;
	if (his == NULL)
		return ;
	while (his->prev != NULL)
		his = his->prev;
	while (his->cmd != NULL)
	{
		free(his->cmd);
		del = his;
		his = his->next;
		free(del);
	}
	his->prev = NULL;
	his->next = NULL;
}

/*
**	Print the 'n' last elements of the history list.
*/

static void		print_n_last_elem(struct s_line *le, unsigned int n)
{
	struct s_history	*his;
	unsigned int		index;

	his = le->history;
	while (his->prev != NULL)
		his = his->prev;
	index = 0;
	while (his->cmd != NULL)
	{
		his = his->next;
		++index;
	}
	if (n > index)
		return ;
	while (n > 0)
	{
		his = his->prev;
		--n;
	}
	while (his->cmd != NULL)
	{
		ft_putstr(his->cmd);
		ft_putchar('\n');
		his = his->next;
	}
}

/*
**	Without option : print the history list with an index.
**	--clear : empty the history.
**	--save : save the history into a file.
**	history n : print the last 'n' elements.
**	-d n : deletes the element with the index 'n'.
*/

void    builtin_history(char **argv, t_environ *env, t_exec *exe)
{
	(void)env;
	exe->ret = 0;
	if (ft_count_elem_2d_array(argv + 1) == 0)
		print_history_with_indexes();
	else if (ft_count_elem_2d_array(argv + 1) == 1)
	{
		if (ft_strequ(argv[1], "--clear"))
			clear_history(access_le_main_datas());
		else if (ft_strequ(argv[1], "--save"))
			exe->ret = save_history_in_file(access_le_main_datas()->history) \
			== true ? (0) : (1);
		else if ( ft_str_is_positive_numeric(argv[1]) == true )
			print_n_last_elem(access_le_main_datas(), ft_atoi(argv[1]));
		else
			ft_putstr_fd(BUILTIN_HISTORY_USAGE, STDERR_FILENO);
	}
	else if (ft_count_elem_2d_array(argv + 1) == 2)
	{
		if (ft_strequ(argv[1], "-d") && ft_str_is_positive_numeric(argv[2]))
			delete_element_number_n(ft_atoi(argv[2]));
		else
			ft_putstr_fd(BUILTIN_HISTORY_USAGE, STDERR_FILENO);
	}
	else
		ft_putstr_fd(BUILTIN_HISTORY_USAGE, STDERR_FILENO);
}
