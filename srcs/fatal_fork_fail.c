/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fatal_fork_fail.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:22:31 by cyfermie          #+#    #+#             */
/*   Updated: 2018/12/04 17:25:34 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void	fatal_fork_fail(void)
{
	const char	*s;

	s = "fatal: fork error - cannot create new processes\n";
	write(STDERR_FILENO, s, ft_strlen(s));
	exit(EXIT_FAILURE);
}
