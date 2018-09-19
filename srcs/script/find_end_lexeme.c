/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_end_lexeme.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 19:11:24 by sbrucker          #+#    #+#             */
/*   Updated: 2018/09/19 19:43:41 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static t_lexeme	*to_end(t_lexeme *lex)
{
	size_t	end_token;
	t_lexeme	*save_lex;

	if (lex->type_details == TK_SCRIPT_IF)
		end_token = TK_SCRIPT_FI;
	else if (lex->type_details == TK_SCRIPT_WHILE)
		end_token = TK_SCRIPT_DONE;
	else
		return (lex);
	log_trace("=to_end %d - %s - %p", end_token, lex->data, lex);
	while (lex && lex->type_details != end_token)
	{
		lex = lex->next;
		save_lex = lex;
		lex = to_end(lex);
		if (save_lex != lex)
			lex = lex->next;
	}
	log_trace("=to_end %d - %s - %p", end_token, lex->data, lex);
	return (lex);
}

t_lexeme	*find_end_lexeme_solo(t_lexeme *start, const size_t end_token)
{
	int			i;
	t_lexeme	*lex;

	i = 0;
	start = start->next;
	//log_trace("===end_token = %d", end_token);
	lex = start;
	while (lex && lex->type_details != end_token)
	{
		//log_trace("==lex_before %s - %p", lex->data, lex);
		lex = to_end(lex);
		lex = lex->next;
		//if (lex)
			//log_trace("==lex_after %s - %p", lex->data, lex);
		//else
			//log_trace("==lex_after NULL");
	}
	if (lex)
	{
		//log_trace("===LEX FOUND %s - %p", lex->data, lex);
		return (lex);
	}
	return (start);
}

t_lexeme	*lex_compete(t_lexeme *lex, const size_t end_token[])
{
	size_t	size_end_token;
	unsigned int		i;
	t_lexeme	**end;
	t_lexeme	*save;
	unsigned int		*paths;
	unsigned int	closest;

	//Initialisation du tableau de token trouve
	size_end_token = 0;
	while (end_token[size_end_token])
		size_end_token++;
	end = (t_lexeme **)ft_memalloc(sizeof(t_lexeme *) * (size_end_token + 1));
	paths = (unsigned int *)ft_memalloc(sizeof(unsigned int) * (size_end_token + 1));
	if (!end)
		exit(MALLOC_ERROR);
	//Boucle pour trouver les tokens
	i = 0;
	while (end_token[i])
	{
		end[i] = find_end_lexeme_solo(lex, end_token[i]);
		i++;
	}
	//Boucle pour calculer le temps de trajet
	i = 0;
	while (end_token[i])
	{
		save = lex;
		while (end[i] && save && save != end[i])
		{
			paths[i]++;
			save = save->next;
		}
		i++;
	}
	//Boucle pour chercher le plus petit trajet
	i = 0;
	closest = -1;
	while (end_token[i])
	{
		//log_debug("path[i] %u", paths[i]);
		if (paths[i] != 1 && closest > paths[i])
			closest = paths[i];
		i++;
	}
	//log_debug("Closest %u", closest);
	//Boucle pour aller au lexeme correspondant
	while (closest--)
		lex = lex->next;
	//log_info("LEX_COMPETE_FOUND: %s - %p", lex->data, lex);
	return (lex);
}

t_lexeme	*find_end_lexeme(t_lexeme *start, const size_t end_token[])
{
	if (!end_token[1])
		return (find_end_lexeme_solo(start, end_token[0]));
	else
		return (lex_compete(start, end_token));
}
