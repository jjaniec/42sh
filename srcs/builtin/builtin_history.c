/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 19:08:07 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/26 19:15:24 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>
/*
t_option		g_history_opts[] = {
	{{"-help"}, "Prints help", false},
	{{"d"}, "Delete element number n", false},
	{{"-clear"}, "Clear history", false},
	{{"-save"}, "Save history in .42shrc/.42sh_history", false},
	{{NULL}, NULL, false}
};
*/
/*
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
*/
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

//	his_debug();
	
}

static bool		save_history_in_file(void)
{le_debug("%s", "SAVE HISTO IN FILE\n");
	int						fd;
	const struct s_history	*his = access_le_main_datas()->history;


	if (check_42shrc() == false)
		return (false);

	if (his == NULL)
		return (true);
	while (his->prev != NULL)
		his = his->prev;
le_debug("%s", "AVANT LE OPEN\n");
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
/*
static void		print_usage(void)
{
	ft_putstr_fd("usage: history [n | -d n | --clear | --save]\n", STDERR_FILENO);
}
*/
static void	_le_free_history(struct s_line *le)
{le_debug("%s", "CLEAR HISTO\n");
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
{le_debug("%s", "BEGIN N LAST ELEM\n");
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

	le_debug("== %d %d\n", index, n);

	if (n > index)
	{
		le_debug("%s", "NOP N NOP N NOP N\n");
		return ;
	}

	while (n > 0)
	{
		his = his->prev;
		--index;
		--n;
	}

	while (his->cmd != NULL)
	{
		ft_putstr(his->cmd);
		ft_putchar('\n');
		his = his->next;
	}

}

static unsigned int		get_nb_args(char **args)
{
	unsigned int	i;

	i = 0;
	while (args[i] != NULL)
		++i;
	return (i);
}

void    builtin_history(char **argv, char **envp, t_exec *exe)
{

	int				ret;
	unsigned int	nb_args;
	//unsigned int	keep_nb_args;
	//char			**keep_argv;

	(void)envp;

	ret = 0;
	nb_args = get_nb_args(argv + 1);
	//keep_nb_args = nb_args;
	//keep_argv = argv;
	//nb_args += 1;
	//argv = parse_options((int *)(&nb_args), argv, g_history_opts, NULL);
	//nb_args -= 1;
	//nb_args = keep_nb_args;
	//argv = keep_argv;
le_debug("HISTO NB ARGS = %u\n", nb_args);
	if (nb_args == 0)
	{
		print_history_with_indexes();
	}
	else if (nb_args == 1)
	{
		// clear ou save ou n
		//if (is_option_activated("-clear", g_history_opts, NULL))
		if (ft_strequ(argv[1], "--clear"))
		{
			_le_free_history(access_le_main_datas());
			//g_history_opts[2].opt_status = false;
		}
		//else if (is_option_activated("-save", g_history_opts, NULL))
		else if (ft_strequ(argv[1], "--save"))
		{
			//le_debug("%s", "CEST MA FAUTE\n");
			ret = save_history_in_file() == true ? (0) : (1);
		}
		else if ( str_is_positive_numeric(argv[1]) == true )
			print_n_last_elem(access_le_main_datas(), ft_atoi(argv[1]));
		else
			ft_putstr_fd(BUILTIN_HISTORY_USAGE, STDERR_FILENO);

	}
	else if (nb_args == 2)
	{
		// -d n
		if ( ft_strequ(argv[1], "-d") && str_is_positive_numeric(argv[2]) == true )
			delete_element_number_n(ft_atoi(argv[2]));
		else
			ft_putstr_fd(BUILTIN_HISTORY_USAGE, STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd(BUILTIN_HISTORY_USAGE, STDERR_FILENO);
	}

	/*
	printf("LOL %s\n", *argv);
	printf(" lol 1 %d lol 2 %d lol 3 %d lol 4 %d\n", is_option_activated("-clear", history_opts, NULL), !is_option_activated("-save", history_opts, NULL), !is_option_activated("d", history_opts, NULL), !argv);
	if (is_option_activated("h", history_opts, NULL))
	{
		format_help(BUILTIN_HISTORY_USAGE, history_opts);
		exit(0);
	}
	if (is_option_activated("-clear", history_opts, NULL) && !is_option_activated("-save", history_opts, NULL) && !is_option_activated("d", history_opts, NULL) && !*argv)
	{
		printf("MDR LOL\n");
		fflush(stdout);
	}
	*/

	// si 2 arguments, il faut que ce soit "-d" et un chiffre positif => delete_element_number_n(ft_atoi(argv[2]));

	// si 1 argument, il faut que ce soit "--clear" ou "--save" => _le_free_history(access_le_main_datas()); ou 
			/*if (check_42shrc() == false)
			{
				exe->ret = 1;
				return ;
			}

			if (save_history_in_file() == false)
			{
				exe->ret = 1;
				return ;
			}*/
	
	// toujours si 1 argument, si c'est un nombre positif => print_n_last_elem(access_le_main_datas(), ft_atoi(argv[1]));

	// si pas d'argument => print_history_with_indexes();

	// sinon => print_usage();

// check si ret est bien mis a jour sur toutes les fonctions d'option
le_debug("RET BUILTIN HISTO = %d\n", ret);
	exe->ret = ret;
}
