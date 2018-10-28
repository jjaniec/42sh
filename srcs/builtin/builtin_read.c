/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 13:18:30 by cyfermie          #+#    #+#             */
/*   Updated: 2018/10/28 18:21:18 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

static void	get_local_vars_names(struct s_bltread *options, char **args)
{

}

static bool	get_activated_options(char **args, struct s_bltread *options)
{
	unsigned int	i;
	unsigned int	nb_words;
	unsigned int	keep_i;

	ft_memset(options, 0, sizeof(struct s_bltread));
	//options->opt_n = true;
	options->nb_opt_nN = BLTREAD_MAX_CH;

	i = 0;
	while (args[i] != NULL && ft_strequ(args[i], "--") == false)
	{
		if (ft_strequ(args[i], "-d"))
		{
			options->opt_d = true;
			if (args[i + 1] != NULL && ft_strlen(args[i + 1]) == 1U)
				options->delim_opt_d = args[i + 1][0];
			else
				return (false);
			i += 2;
			if (args[i] == NULL)
				return (true);
			i -= 1;
		}
		else if (ft_strequ(args[i], "-n"))
		{
			options->opt_n = true;
			if (args[i + 1] != NULL && ft_strequ(args[i + 1], "-n") == false
			&& ft_strequ(args[i + 1], "-N") == false
			&& ft_strequ(args[i + 1], "-p") == false
			&& ft_strequ(args[i + 1], "-s") == false
			&& ft_strequ(args[i + 1], "-d") == false  )
				options->nb_opt_nN = ft_atoi(args[i + 1]);
			else
				return (false);
			i += 2;
			if (args[i] == NULL)
				return (true);
			i -= 1;
		}
		else if (ft_strequ(args[i], "-N"))
		{
			options->opt_N = true;
			if (args[i + 1] != NULL && ft_strequ(args[i + 1], "-n") == false
			&& ft_strequ(args[i + 1], "-N") == false
			&& ft_strequ(args[i + 1], "-p") == false
			&& ft_strequ(args[i + 1], "-s") == false
			&& ft_strequ(args[i + 1], "-d") == false  )
				options->nb_opt_nN = ft_atoi(args[i + 1]);
			else
				return (false);
			i += 2;
			if (args[i] == NULL)
				return (true);
			i -= 1;
		}
		else if (ft_strequ(args[i], "-p"))
			options->opt_p = true;
		else if (ft_strequ(args[i], "-s"))
			options->opt_s = true;
		else
			return (false);
		++i;
	}

	nb_words = 0;
	keep_i = i;
	while (args[i] != NULL)
	{
		if (ft_strequ(args[i], "--") == false)
			++nb_words;
		++i;
	}
	i = keep_i;
	options->words_vars = ft_xmalloc(sizeof(char *) * (nb_words + 1));
	options->words_vars[nb_words] = NULL;

	unsigned int	j = 0;
	while (args[i] != NULL)
	{
		if (ft_strequ(args[i], "--") == false)
			options->words_vars[j++] = args[i];
		++i;
	}
/*
	{ le_debug("NB WORDS VAR = %u\n", nb_words) }
	if (nb_words > 0)
		for (int i = 0 ; options->words_vars[i] != NULL ; ++i)
			{ le_debug("WORD %d %s\n", i, options->words_vars[i]) }
*/
	return (true);
}


void	builtin_read(char **argv, t_environ *env, t_exec *exe)
{
	struct s_bltread	options;
	unsigned char		*buffer;

	g_cmd_status.builtin_running = true;

	//(void)exe;
	(void)(env);
	//exe->ret = 0;
	if (get_activated_options(argv + 1, &options) == false
	|| (options.opt_n == true && options.opt_N == true))
	{
		ft_putstr_fd(BUILTIN_READ_USAGE, STDERR_FILENO);
		exe->ret = 1;
		//exit(1);
		g_cmd_status.builtin_running = false;
		free(options.words_vars);
		return ;
	}
	options.opt_n = true;
	if (options.opt_N == true)
		options.opt_d = false;
	if (options.nb_opt_nN > BLTREAD_MAX_CH)
		options.nb_opt_nN = BLTREAD_MAX_CH;
	if (options.nb_opt_nN == 0)
	{
		g_cmd_status.builtin_running = false;
		free(options.words_vars);
		return ;
		//exit(0);
	}

	// DEBUG
	{
		le_debug("d = %s\nn = %s\nN = %s\np = %s\ns = %s\n",
		options.opt_d == true ? "true" : "false",
		options.opt_n == true ? "true" : "false",
		options.opt_N == true ? "true" : "false",
		options.opt_p == true ? "true" : "false",
		options.opt_s == true ? "true" : "false"      );

		if (options.opt_d == true)
		{
			{ le_debug("delim opt d = '%c'\n", options.delim_opt_d) }
		}
		if (options.opt_n == true || options.opt_N == true)
		{
			{ le_debug("nb opt n N = %u\n", options.nb_opt_nN) }
		}


	}


	unsigned char	delim = '\n';
	unsigned int	nb_ch = 0;
	ssize_t			ret;
	buffer = ft_xmalloc(BLTREAD_MAX_CH + 1); // penser a free
	ft_memset(buffer, '\0', BLTREAD_MAX_CH + 1);

	if (options.opt_d == true)
		delim = options.delim_opt_d;

	struct termios t;
	tcgetattr(STDIN_FILENO, &t);
	t.c_lflag &= ~(ICANON);
	if (options.opt_s)
		t.c_lflag &= ~(ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &t);

	if (options.opt_p == true)
		write(STDOUT_FILENO, "> ", 2);

	while ("read")
	{
		ret = read(STDIN_FILENO, buffer + nb_ch, 1);
		if (ret == -1)
		{
			if (errno == EINTR)
			{
				// faire les free
				t.c_lflag |= (ICANON | ECHO);
				tcsetattr(STDIN_FILENO, TCSANOW, &t);
				g_cmd_status.builtin_running = false;
				write(STDOUT_FILENO, "\n", sizeof(char));
				free(options.words_vars);
				free(buffer);
				return ;
			}
			else
				exit(EXIT_FAILURE);
		}


		nb_ch += 1;

		if (options.opt_N == false
		&& ((options.opt_d == true && buffer[nb_ch - 1] == options.delim_opt_d)
		|| (options.opt_d == false && buffer[nb_ch - 1] == '\n')))
		{
			buffer[nb_ch - 1] = '\0';
			break ;
		}
		else if (options.opt_N == true || options.opt_n == true)
		{
			if (nb_ch == options.nb_opt_nN)
				break ;
		}

	}

	t.c_lflag |= (ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &t);

	//printf("\nbuffer = |%s|\n", buffer);

	//exit(0);
	g_cmd_status.builtin_running = false;
	free(options.words_vars);
	free(buffer);
}

/*
	read on stdin

	store the words in given arguments

	the words spliting is done using IFS

	if there are more words than arguments, the last arg will have all the remaining words

	if there is no argument given, REPLY is used to store all the words

	by default the end of reading is '\n'


	OPTIONS
	{
		-d x  change the delimiter ('\n' by default) to x
		-n x  read stops itself if receiving the delimiter character or if it has read x characters
		-N x  ignore the delimiter character, read stops if it has read x characters or encountering EOF
		-p    prints a prompt before reading
		-s    pas d'affichage de l'input

	}

	{

	}


n et N peuvent pas etre ensemble

*/