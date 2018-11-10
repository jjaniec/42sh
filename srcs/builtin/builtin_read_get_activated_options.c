/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_read_get_activated_options.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 17:40:33 by cyfermie          #+#    #+#             */
/*   Updated: 2018/11/10 20:28:18 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

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
	{ le_debug("MALLOC DE %u WORDS\n", nb_words + 1) }
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

bool		_norme_lol(int foo, char **args, unsigned int i)
{
	if (foo == 1)
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

int		_norme_mdr(int foo, struct s_bltread *options, char **args, unsigned int *i)
{
	if (foo == 1)
	{
		ft_memset(options, 0, sizeof(struct s_bltread));
		options->nb_opt_nN = BLTREAD_MAX_CH;
		*i = 0;
		return (2);
	}
	options->opt_N = true;
	if (_norme_lol(2, args, *i) == true)
		options->nb_opt_nN = ft_atoi(args[*i + 1]);
	else
		return (0);
	*i += 2;
	if (args[*i] == NULL)
		return (1);
	*i -= 1;
	return (2);
}

bool	_get_activated_options(char **args, struct s_bltread *options,
												bool fou, int janice)
{
	unsigned int	i;

	_norme_mdr(1, options, args, &i);
	while (args[i] != NULL && ft_strequ(args[i], "--") == false)
	{
		if (ft_strequ(args[i], "-d") \
		&& (janice = _a(options, args, &i, &fou)) != 2)
			return (janice);
		else if ((ft_strequ(args[i], "-n")) \
		&& (janice = _a2(options, args, &i, &fou)) != 2)
			return (janice);
		else if (ft_strequ(args[i], "-N") \
		&& (janice = _amdr(options, args, &i, &fou)) != 2)
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
