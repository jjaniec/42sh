/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 19:08:07 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/24 19:40:38 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

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

static bool	str_is_numeric(const char *str)
{
	while (*str != '\0')
	{
		if (*str < '0' || *str > '9')
			return (false);
		++str;
	}
	return (true);
}

void    builtin_history(char **argv, char **envp, t_exec *exe)
{le_debug("%s", " - - - - - BUILTIN HISTORY\n");

	(void)envp;

	if (argv[1] != NULL && argv[2] != NULL)
	{
		// trop d'arguments, usage

	}
	else if (argv[1] != NULL)
	{
		// check quel est l'option pour lancer le bon comportement
	}

	else
	{
		print_history_with_indexes();
	}


	exit(0);
}


/*
	go faire une fonction au debut du main qui check et cree si necessaire le dossier .42sh
	avec dedans le fichier .42sh_alias et le fichier .42sh_history dont je m'occupe

	il peut y avoir 0 argument ou 1 mais pas plus

	sans aucun argument, go afficher lhistorique avecun numero a cote,
	l'element le plus vieux cest 1

	si ya 1 argument et qu'il est numerique, go afficher les n derniers elements 
	(avec leur vrai numero, genre si n == 4 les numeros c'est pas 1 a 4 
	(sauf si ya que 4 elements lol) )

	--clear ca supprime tout l'historique (la liste chainee seulement)

	-d n  delete l'element numero n (dans la liste seulement)

	--save  copie la liste chainee dans le fichier (si la liste est vide, le fichier sera vidé)

*/
