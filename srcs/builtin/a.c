/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 19:44:19 by sbrucker          #+#    #+#             */
/*   Updated: 2018/11/09 20:25:32 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

int		norme_mdr(int foo, struct s_bltread *options, char **args, unsigned int *i);

bool		norme_lol(int foo, char **args, unsigned int i)
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
            return (0);
		*i = *i + 2;
		if (args[*i] == NULL)
			return (1);
		*i = *i - 1;
		return (2);
	}
	options->opt_n = true;
	if (norme_lol(1, args, *i) == true)
		options->nb_opt_nN = ft_atoi(args[*i + 1]);
	else
		return (0);
	*i += 2;
	if (args[*i] == NULL)
		return (1);
	*i -= 1;
	return (2);
}

int		amdr(struct s_bltread *options, char **args, unsigned int *i, bool *fou)
{
	int janice;

	janice = norme_mdr(2, options, args, i);
	if (janice == 2)
		*fou = true;
	else 
		return ( janice == 0 ? false : true );

	return 2;
}

int		a2(struct s_bltread *options, char **args, unsigned int *i, bool *fou)
{
	int janice;

	janice = norme_lel(2, options, args, i);
	if (janice == 2)
		*fou = true;
	else 
		return ( janice == 0 ? false : true );

	return 2;
}

int		a(struct s_bltread *options, char **args, unsigned int *i, bool *fou)
{
	int janice;

	janice = norme_lel(1, options, args, i);
	if (janice == 2)
		*fou = true;
	else 
		return ( janice == 0 ? false : true );

	return 2;
}
