/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_read_get_activated_options.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 17:40:33 by cyfermie          #+#    #+#             */
/*   Updated: 2018/11/09 20:31:47 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

int		a(struct s_bltread *options, char **args, unsigned int *i, bool *fou);
int		amdr(struct s_bltread *options, char **args, unsigned int *i, bool *fou);
int		a2(struct s_bltread *options, char **args, unsigned int *i, bool *fou);
bool	norme_lol(int foo, char **args, unsigned int i);

static bool	get_local_vars_names(struct s_bltread *options, char **args, unsigned int i)
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
	options->words_vars = ft_xmalloc(sizeof(char *) * (nb_words + 1));
	options->words_vars[nb_words] = NULL;
	j = 0;
	while (args[i] != NULL)
	{
		if (ft_strequ(args[i], "--") == false)
			options->words_vars[j++] = args[i];
		++i;
	}
    return (true);
}

int		norme_mdr(int foo, struct s_bltread *options, char **args, unsigned int *i)
{
	if (foo == 1)
	{
		ft_memset(options, 0, sizeof(struct s_bltread));
		options->nb_opt_nN = BLTREAD_MAX_CH;
		*i = 0;
		return (2);
	}
	options->opt_N = true;
	if (norme_lol(2, args, *i) == true)
		options->nb_opt_nN = ft_atoi(args[*i + 1]);
	else
		return (0);
	*i += 2;
	if (args[*i] == NULL)
		return (1);
	*i -= 1;
	return (2);
}

bool	_get_activated_options(char **args, struct s_bltread *options, \
		bool fou, int janice)
{
	unsigned int	i;

	norme_mdr(1, options, args, &i);
	while (args[i] != NULL && ft_strequ(args[i], "--") == false)
	{
		if (ft_strequ(args[i], "-d") \
		&& (janice = a(options, args, &i, &fou)) != 2)
			return (janice);
		else if ((ft_strequ(args[i], "-n")) \
		&& (janice = a2(options, args, &i, &fou)) != 2)
			return (janice);
		else if (ft_strequ(args[i], "-N") \
		&& (janice = amdr(options, args, &i, &fou)) != 2)
			return (janice);
		else if (ft_strequ(args[i], "-p"))
			options->opt_p = true;
		else if (ft_strequ(args[i], "-s"))
			options->opt_s = true;
		else if (fou == false)
			return (false);
		i++;
		fou = true;
	}
	return (get_local_vars_names(options, args, i));
}
