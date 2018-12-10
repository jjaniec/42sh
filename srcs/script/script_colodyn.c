/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script_colodyn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 14:24:34 by sbrucker          #+#    #+#             */
/*   Updated: 2018/10/26 14:49:34 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

int		script_colodyn(t_lexeme *lex, int *item_nb)
{
	int		found;
	char	*data;

	data = ft_str_capitalize(ft_xstrdup(lex->data));
	found = 0;
	found += ft_strequ(data, "IF");
	found += ft_strequ(data, "ELIF");
	found += ft_strequ(data, "ELSE");
	found += ft_strequ(data, "THEN");
	found += ft_strequ(data, "WHILE");
	found += ft_strequ(data, "DO");
	*item_nb -= found;
	found += ft_strequ(data, "FI");
	found += ft_strequ(data, "DONE");
	found += ft_strequ(data, "BREAK");
	found += ft_strequ(data, "CONTINUE");
	free(data);
	return (found);
}
