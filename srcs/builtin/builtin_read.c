/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 13:18:30 by cyfermie          #+#    #+#             */
/*   Updated: 2018/11/08 19:38:43 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

static void	get_local_vars_names(struct s_bltread *options, char **args, unsigned int i)
{
	unsigned int	nb_words;
	unsigned int	keep_i;
	unsigned int	j;

	nb_words = 0;
	keep_i = i;
	while (args[i] != NULL)
	{
		if (ft_strequ(args[i], "--") == false)
			++nb_words;
		++i;
	}
	i = keep_i;
	options->words_vars = ft_xmalloc(sizeof(char *) * (nb_words + 1));   { le_debug("ALLOCATION WORDS VAR %p\n", options->words_vars) }
	options->words_vars[nb_words] = NULL;

	j = 0;
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
}

static bool	norme_lol(int foo, char **args, unsigned int i)
{
	if (foo == 0)
	{

	}
	else if (foo == 1)
	{
		if (args[i + 1] != NULL && ft_strequ(args[i + 1], "-n") == false
		&& ft_strequ(args[i + 1], "-N") == false
		&& ft_strequ(args[i + 1], "-p") == false
		&& ft_strequ(args[i + 1], "-s") == false
		&& ft_strequ(args[i + 1], "-d") == false  )
			return (true);
		return (false);
	}
	else if (foo == 2)
	{
		if (args[i + 1] != NULL && ft_strequ(args[i + 1], "-n") == false
		&& ft_strequ(args[i + 1], "-N") == false
		&& ft_strequ(args[i + 1], "-p") == false
		&& ft_strequ(args[i + 1], "-s") == false
		&& ft_strequ(args[i + 1], "-d") == false  )
			return (true);
		return (false);
	}

	return (true && false || true ^ false);
}

static int	norme_lel(int foo, struct s_bltread *options, char **args, unsigned int *i)
{
	if (foo == 1)
	{
		options->opt_d = true;
		if (args[*i + 1] != NULL && ft_strlen(args[*i + 1]) == 1U)
			options->delim_opt_d = args[*i + 1][0];
		else
			{  { le_debug("%s\n", "RETOURNAGE DE FALSE") } return (0);  } // false
		*i = *i + 2;
		if (args[*i] == NULL)
			return (1); // true
		*i = *i - 1;
		return (2);
	}
	options->opt_n = true;
	if (norme_lol(1, args, *i) == true)
		options->nb_opt_nN = ft_atoi(args[*i + 1]);
	else
		return (0); // false
	*i += 2;
	if (args[*i] == NULL)
		return (1); // true
	*i -= 1;
	return (2);
}

static int	norme_ptdr(int foo, struct s_bltread *options, char **args, unsigned int *i)
{
	if (foo == 1)
	{
		ft_memset(options, 0, sizeof(struct s_bltread)); //options->words_vars = NULL;
		options->nb_opt_nN = BLTREAD_MAX_CH;
		*i = 0;
		return (2);
	}

	options->opt_N = true;
	if (norme_lol(2, args, *i) == true)
		options->nb_opt_nN = ft_atoi(args[*i + 1]);
	else
		return (0); // false
	*i += 2;
	if (args[*i] == NULL)
		return (1); // true
	*i -= 1;
	return (2);
}

static bool	get_activated_options(char **args, struct s_bltread *options)
{
	unsigned int	i;
	int				janice;
	bool			fou = false;

	norme_ptdr(1, options, args, &i);
	while (args[i] != NULL && ft_strequ(args[i], "--") == false)
	{
		if (ft_strequ(args[i], "-d")
		&& (((janice = norme_lel(1, options, args, &i)) != 2) || !(fou = true)))
			return (janice == 0 ? false : true);
		else if (ft_strequ(args[i], "-n")
		&& (((janice = norme_lel(2, options, args, &i)) != 2) || !(fou = true)))
			return (janice == 0 ? false : true);
		else if (ft_strequ(args[i], "-N")
		&& (((janice = norme_ptdr(2, options, args, &i)) != 2) || !(fou = true)))
			return (janice == 0 ? false : true);
		else if (ft_strequ(args[i], "-p"))
			options->opt_p = true;
		else if (ft_strequ(args[i], "-s"))
			options->opt_s = true;
		else
		{
			if (fou == false)
			{
				{ le_debug("%s\n", "FALSEUUUH") }
				return (false);
			}
		}
		++i;
		fou = true;
	}
	{ le_debug("%s\n", "ON QUITTE LE WHILE") } // debug
	get_local_vars_names(options, args, i);
	return (true);
}

static void	prepare_reading_line(struct termios *t, unsigned char **buffer, struct s_bltread *options/*, unsigned char *delim*/)
{
	*buffer = ft_xmalloc(BLTREAD_MAX_CH + 1);
	ft_memset(*buffer, '\0', BLTREAD_MAX_CH + 1);
	//if (options->opt_d == true)
	//	*delim = options->delim_opt_d;
	tcgetattr(STDIN_FILENO, t); // check
	t->c_lflag &= ~(ICANON);
	if (options->opt_s == true)
		t->c_lflag &= ~(ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, t); // check
	if (options->opt_p == true)
		write(STDOUT_FILENO, "> ", 2);


}

static int		read_loop(unsigned char *buffer, /*unsigned char delim,*/ struct s_bltread *options)
{
	unsigned int	nb_ch;

	nb_ch = 0;
	while ("read")
	{
		if (read(STDIN_FILENO, buffer + nb_ch, 1) == -1)
		{
			if (errno == EINTR)
				return (1);
			else
				exit(EXIT_FAILURE);
		}
		nb_ch += 1;
		if (options->opt_N == false
		&& ((options->opt_d == true && buffer[nb_ch - 1] == options->delim_opt_d)
		|| (options->opt_d == false && buffer[nb_ch - 1] == '\n')))
		{
			buffer[nb_ch - 1] = '\0';
			break ;
		}
		else if (options->opt_N == true || options->opt_n == true)
			if (nb_ch == options->nb_opt_nN)
				break ;
	}
	return (0);
}

unsigned char	*read_line(struct s_bltread *options)
{
	struct termios	t;
	unsigned char	*buffer;
	//unsigned char	delim;
	int				ret;

	//delim = '\n';
	prepare_reading_line(&t, &buffer, options/*, &delim*/);

	ret = read_loop(buffer, /*delim,*/ options);

	t.c_lflag |= (ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &t); // check

	if (ret == 1)
	{
		g_cmd_status.builtin_running = false;
		write(STDOUT_FILENO, "\n", sizeof(char));
		free(options->words_vars);
		options->words_vars = NULL;
		free(buffer);
		buffer = NULL;
		return (NULL);
	}

	return (buffer);
}

static bool	prepare_blt_read(char **argv, struct s_bltread *options, t_exec *exe)
{
	if (get_activated_options(argv + 1, options) == false
	|| (options->opt_n == true && options->opt_N == true))
	{
		{ le_debug("%s\n", "ON QUITTE ICI") }	// debug
		ft_putstr_fd(BUILTIN_READ_USAGE, STDERR_FILENO);
		exe->ret = 1;
		g_cmd_status.builtin_running = false;
		free(options->words_vars);
		return (false);
	}
	options->opt_n = true;
	if (options->opt_N == true)
		options->opt_d = false;
	if (options->nb_opt_nN > BLTREAD_MAX_CH)
		options->nb_opt_nN = BLTREAD_MAX_CH;
	if (options->nb_opt_nN == 0)
	{
		g_cmd_status.builtin_running = false;
		free(options->words_vars);
		return (false);
	}
	return (true);
}

static char		**split_buffer_with_ifs(unsigned char *buffer)
{
	char	**split;

char	**ft_strsplit_bystr(char const *s, const char *split); // proto en attendant libft

	split = ft_strsplit_bystr((const char *)buffer, LE_IFS);
	if (split == NULL)
		exit(MALLOC_ERROR);
	return (split);
}

static void	coco_bichon_lox(t_shell_vars *vars, char **split, unsigned int i)
{
	ft_strncat(vars->locals->last_used_elem->val_begin_ptr, " ", \
	MAX_ENV_ENTRY_LEN - \
	ft_strlen(vars->locals->last_used_elem->entry));
	ft_strncat(vars->locals->last_used_elem->val_begin_ptr, split[i], \
	MAX_ENV_ENTRY_LEN - \
	ft_strlen(vars->locals->last_used_elem->entry));
}

static void	sebateau(char **split, struct s_bltread *options, char *var_name,
														t_shell_vars *vars)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (!(*(options->words_vars)))
		vars->locals->del_var(vars->locals, "REPLY");
	else
	{
		while (options->words_vars[i])
			vars->locals->del_var(vars->locals, options->words_vars[i++]);
	}
	i = 0;
	while (split[i])
	{
		if (options->words_vars[j])
			var_name = options->words_vars[j];
		if (!(vars->locals->get_var(vars->locals, var_name)))
			vars->locals->add_var(vars->locals, var_name, split[i]);
		else
		{
			if (ft_strequ(var_name, "REPLY") || !(options->words_vars[j + 1]))
				coco_bichon_lox(vars, split, i);
			else
				ft_strncpy(vars->locals->last_used_elem->val_begin_ptr, \
				split[i], MAX_ENV_ENTRY_LEN);
		}
		i++;
		if (options->words_vars[j] && options->words_vars[j + 1])
			j++;
	}
}

static void	store_words_in_shell_variables(unsigned char *buffer,
										struct s_bltread *options)
{
	t_shell_vars	*vars;
	char			*var_name;
	char			**split;

	split = split_buffer_with_ifs(buffer);
	var_name = "REPLY";
	vars = get_shell_vars();
	sebateau(split, options, var_name, vars);
	ft_free_2d_array(split);

}


void	builtin_read(char **argv, t_environ *env, t_exec *exe)
{
	struct s_bltread	options;
	unsigned char		*buffer;

	g_cmd_status.builtin_running = true;

	(void)(env);
	if (prepare_blt_read(argv, &options, exe) == false)
		return ;

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

	buffer = read_line(&options);
	if (buffer != NULL)
		store_words_in_shell_variables(buffer, &options);


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