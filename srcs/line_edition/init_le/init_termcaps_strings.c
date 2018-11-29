/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_termcaps_strings.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 20:00:25 by cyfermie          #+#    #+#             */
/*   Updated: 2018/10/20 18:43:30 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**	Initialize some termcaps that will be used for the shell internal behavior.
*/

struct s_le_termcaps	*init_termcaps_strings(void)
{
	static struct s_le_termcaps tc;
	const char					**index;
	unsigned int				i;
	const char					*tcaps_names[] = {
		"nd", "le", "do", "up", "dc", "cl", "md", "me", "cr", "cd", "dl", "al",
		"us", "mr", "ue"
	};

	index = (const char **)(&tc);
	i = 0;
	while ((ptrdiff_t)((uintptr_t)index - (uintptr_t)(&tc))
	< (ptrdiff_t)sizeof(tc))
	{
		*index = tgetstr((char *)(tcaps_names[i]), NULL);
		if (*index == NULL)
		{
			ft_putstr_fd(SH_NAME ": Failed to initialize '", 2);
			ft_putstr_fd(tcaps_names[i], 2);
			ft_putstr_fd("' termcap\n", 2);
			exit(EXIT_FAILURE);
		}
		index = (const char **)(((uintptr_t)index) + sizeof(const char *));
		++i;
	}
	return (&tc);
}
