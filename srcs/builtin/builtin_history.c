/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 19:08:07 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/25 19:52:19 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static void	his_debug(void)
{
	struct s_history *h = access_le_main_datas()->history;

	while (h->prev != NULL)
		h = h->prev;

	le_debug("%s", "HIS linked list\n");
	while (h != NULL)
	{
		le_debug("|%s|\n", h->cmd);
		h = h->next;
	}
	le_debug("%s","HIS END\n");
}

static unsigned int	get_nb_elem_in_history(void)
{
	struct s_history	*his;
	unsigned int		nb_elem;

	nb_elem = 0;
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

static void	print_history_with_indexes(void)
{
	const struct s_history	*his = access_le_main_datas()->history;
	unsigned int			index;
	unsigned int			nb_elem;

	nb_elem = get_nb_elem_in_history();

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


			write(STDOUT_FILENO, his->cmd, ft_strlen(his->cmd));
			write(STDOUT_FILENO, "\n", sizeof(char));
			his = his->next;
			++index;
		}


	}
	else
		le_debug("%s", "BAH ALORS LE HISTORY IL EST OU BORDEL\n");

	//write(STDOUT_FILENO, "\n", sizeof(char));
}

static bool	str_is_positive_numeric(const char *str)
{
	while (*str != '\0')
	{
		if (*str < '0' || *str > '9')
			return (false);
		++str;
	}
	return (true);
}

static void		delete_element_number_n(unsigned int n)
{le_debug("%s", " - - - - - DEL NUMBER N\n");
	struct s_history	*his;
	struct s_history	*del;
	unsigned int		index;

	//reset_history_on_first_elem(le);
	his = access_le_main_datas()->history;
	if (his == NULL)
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
le_debug(" - - - - - DEL EFFECTIVE on |%s|\n", del->cmd);
	if (access_le_main_datas()->history == del)
		reset_history_on_first_elem(access_le_main_datas());

	his->prev->next = his->next;
	his->next->prev = his->prev;


	free(del->cmd);
	free(del);

	his_debug();
	
}

static bool		save_history_in_file(void)
{
	int						fd;
	const struct s_history	*his = access_le_main_datas()->history;

	if (his == NULL)
		return (true);
	while (his->prev != NULL)
		his = his->prev;

	errno = 0;
	fd = open(_42SHRC_PATH "/.42sh_history", O_WRONLY | O_TRUNC);
	if (fd == 1)
	{
		perror("42sh: error with file .42shrc/.42sh_history\n");
		return (false);
	}

	while (his->cmd != NULL)
	{
		if (write(fd, his->cmd, ft_strlen(his->cmd)) == (ssize_t)-1
		|| write(fd, "\n", sizeof(char)) == (ssize_t)-1)
		{
			ft_putstr_fd(".42shrc/.42sh_history: error while writing in file\n", \
			STDERR_FILENO);
			return (false);
		}


		his = his->next;
	}

	return (true);
}

static void		print_usage(void)
{
	ft_putstr_fd("usage: history [-d n, --clear, --save]\n", STDERR_FILENO);
}

static void	_le_free_history(struct s_line *le)
{
	struct s_history	*his;
	struct s_history	*del;

	his = le->history;
	if (his == NULL)
		return ;
	while (his->prev != NULL)
		his = his->prev;
	while (his != NULL)
	{
		if (his->cmd == NULL)
			break ;

		free(his->cmd);
		del = his;
		his = his->next;
		free(del);
	}
	his->prev = NULL;
	his->next = NULL;
}

static void		print_n_last_elem(struct s_line *le, unsigned int n)
{/*
	struct s_history	*his;
	struct s_history	*first;
	unsigned int		nb_elem;

	his = le->history;
	while (his->prev != NULL)
		his = his->prev;
	first = his;
	nb_elem = 0;
	while (his->cmd != NULL)
	{
		++nb_elem;
		his = his->next;
	}
	his = first;
	while (nb_elem > n)
	{
		his = his->next;
		--nb_elem;
	}
*/
(void) le; (void) n;
	//print_history_with_indexes(n);

}

void    builtin_history(char **argv, char **envp, t_exec *exe)
{le_debug(" - - - - - BUILTIN HISTORY pid %d\n", (int)getpid() );

	int		ret;
	(void)envp;

	ret = 0;
	if (argv[1] != NULL && ft_strcmp(argv[1], "-d") == 0 && argv[2] != NULL
	&& str_is_positive_numeric(argv[2]) == true)
	{
		// -d n
		if (argv[3] != NULL)
		{
			print_usage();
			ret = 1;
			return ;
		}
		delete_element_number_n(ft_atoi(argv[2]));
	}
	else if (argv[1] != NULL && argv[2] == NULL)
	{
		// check quel est l'option pour lancer le bon comportement
		if (ft_strcmp(argv[1], "--clear") == 0)
		{//le_debug("%s", " - - - - - HIS CLEAR\n");
			_le_free_history(access_le_main_datas());
		}
		else if (ft_strcmp(argv[1], "--save") == 0)
		{
			if (check_42shrc() == false)
			{
				exe->ret = 1;
				return ;
			}

			if (save_history_in_file() == false)
			{
				exe->ret = 1;
				return ;
			}
		}
		else if (str_is_positive_numeric(argv[1]))
		{
			print_n_last_elem(access_le_main_datas(), ft_atoi(argv[1]));
		}
		else
		{
			print_usage();
			ret = 1;
		}
	}

	else if (argv[1] == NULL)
	{
		print_history_with_indexes();
	}
	else
	{
		print_usage();
		ret = 1;
	}

le_debug("%s", " - - - - - END BUILTIN HISTORY\n");

	exe->ret = ret;
}
