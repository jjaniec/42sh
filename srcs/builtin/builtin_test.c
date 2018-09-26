/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 12:13:57 by sbrucker          #+#    #+#             */
/*   Updated: 2018/09/26 15:27:07 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** WIP IN PROGRESS IN NEW BRANCH !!
*/

/*
** Posix options
** http://pubs.opengroup.org/onlinepubs/9699919799/utilities/test.html
*/

t_option		g_tests_opts[] = {
	{{"h"}, "-h:\t\tPrint this help with all the options listed.", false},
	{{"b"}, "-b file:\tTrue if file exists and is a block special file.", false},
	{{"c"}, "-c file:\tTrue if file exists and is a character special file.", false},
	{{"d"}, "-d file:\tTrue if file exists and is a directory.", false},
	{{"e"}, "-e file:\tTrue if file exists (regardless of type).", false},
	{{"f"}, "-f file:\tTrue if file exists and is a regular file.", false},
	{{"p"}, "-p file:\tTrue if file is a named pipe (FIFO).", false},
	{{"r"}, "-r file:\tTrue if file exists and is readable.", false},
	{{"s"}, "-s file:\tTrue if file exists and has a size greater than zero.", false},
	{{"w"}, "-w file:\tTrue if file exists and is writable.\n\
			\tTrue indicates only that the write flag is on.\n\
			\tThe file is not writable on a read-only file system even if this test indicates true.", false},
	{{"x"}, "-x file:\tTrue if file exists and is executable.\n\
			\tTrue indicates only that the execute flag is on.\n\
			\tThe file is not executable on a read-only file system even if this test indicates true.", false},
	{{"L"}, "-L file:\tTrue if file exists and is a symbolic link.", false},
	{{"S"}, "-S file:\tTrue if file exists and is a socket.", false},
	{{"--------------------------"}, "" , false},
	{{"n"}, "-n  string:\tTrue if the length of string is nonzero.", false},
	{{"z"}, "-z  string:\tTrue if the length of string is zero.", false},
	{{"="}, "-=  s1 s2:\tTrue if the strings s1 and s2 are identical.", false},
	{{"!="}, "-!= s1 s2:\tTrue if the strings s1 and s2 are not identical.", false},
	{{"<"}, "-<  s1 s2:\tTrue if the strings s1 comes before s2 based on the binary value of their characters.", false},
	{{">"}, "->  s1 s2:\tTrue if the strings s1 comes after s2 based on the binary value of their characters.", false},
	{{"--------------------------"}, "" , false},
	{{"eq"}, "-eq n1 n2:\tTrue if the intengers n1 and n2 are algebraically equal.", false},
	{{"ne"}, "-ne n1 n2:\tTrue if the intengers n1 and n2 are not algebraically equal.", false},
	{{"gt"}, "-gt n1 n2:\tTrue if the intengers n1 is algebraically greater than the integer n2.", false},
	{{"ge"}, "-ge n1 n2:\tTrue if the intengers n1 is algebraically greater than or equal to the integer n2.", false},
	{{"lt"}, "-gt n1 n2:\tTrue if the intengers n1 is algebraically less than the integer n2.", false},
	{{"le"}, "-ge n1 n2:\tTrue if the intengers n1 is algebraically less than or equal to the integer n2.", false},
	{{NULL}, NULL, false}
};
/*
static int	right_format_builtin(char **argv, int *argc)
{
	if (ft_strequ(argv[0], "test"))
		return (1);
	else if (ft_strequ(argv[0], "[") && ft_strequ(argv[*argc - 1], "]"))
	{
		argv[*argc - 1] = NULL;
		(*argc)--;
		return (1);
	}
	else
		return (0);
}

static int	parse_expr(char **argv, t_option *opt_list, \
			t_option *char_opt_index[CHAR_OPT_INDEX_SIZE])
{
	(void)opt_list;
	(void)char_opt_index;
	(void)argv;
	return (0);
}*/

void		builtin_test(char **argv, char **envp, t_exec *exe)
{
	//t_option	*opt_list;
	//t_option	*char_opt_index[CHAR_OPT_INDEX_SIZE];
	//char		**args;
	int			ac;

	(void)envp;
	ac = 0;
	while (argv[ac])
		ac++;

	exe->ret = ft_atoi(argv[1]);
	exit (exe->ret);
	//opt_list = g_tests_opts;
	//args = parse_options(&ac, argv, opt_list, (t_option **)char_opt_index);
	/*if (!argv[0])
		exit (1);
	else if (is_option_activated("h", opt_list, char_opt_index) || \
	is_option_activated("--------------------------", opt_list, char_opt_index)\
	|| !right_format_builtin(argv, &ac))
	{
		//format_help(BUILTIN_TEST_USAGE, opt_list);
		exit (0);
	}
	else if (!argv[1] && ft_strlen(argv[0]) > 0)
		exit (0);
	else if (!argv[1])
		exit (1);
	else
		exit (parse_expr((argv + 1), opt_list, char_opt_index));*/
}
