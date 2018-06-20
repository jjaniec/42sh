/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 16:19:06 by jjaniec           #+#    #+#             */
/*   Updated: 2018/06/20 16:19:32 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static void lexer_loop(void)
{
	char	*input;

	input = malloc(sizeof(char) * 200);
	while (1)
	{
		read(STDIN_FILENO, input, 200);
		lexer(input);
		ft_bzero(input, 200);
	}
	free(input);
}

int	main(int ac, char **av)
{
	if (!DEBUG)
		log_set_quiet(1);
	if (ac > 1)
		lexer(ft_strdup(av[1]));
	else
		lexer_loop();
	return (0);
}
