/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 16:19:06 by jjaniec           #+#    #+#             */
/*   Updated: 2018/06/21 18:33:59 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static void lexer_loop(void)
{
  t_lexeme	*lex;
	char	*input;

	input = malloc(sizeof(char) * 200);
	while (1)
	{
		read(STDIN_FILENO, input, 200);
		lex = lexer(input);
    ast(lex);
		ft_bzero(input, 200);
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
