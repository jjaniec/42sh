/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 16:19:06 by jjaniec           #+#    #+#             */
/*   Updated: 2018/07/19 16:22:16 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static void lexer_loop(void)
{
  t_lexeme	*lex;
	char	*input;

tty_debug = fopen(TTY_DEBUG, "w");
	while (1)
	{
		ft_putstr("%> ");
		input = line_edition();
		lex = lexer(input);
   		 ast(lex);
	}
	free(input);
}

int	main(int ac, char **av)
{
  t_lexeme	*lex;
  
  if (!DEBUG)
		log_set_quiet(1);
	if (ac > 1)
  {
		lex = lexer(ft_strdup(av[1]));
	  ast(lex);
  }
	else
		lexer_loop();
	return (0);
}
