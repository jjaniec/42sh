/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_termcaps_strings.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 20:00:25 by cyfermie          #+#    #+#             */
/*   Updated: 2018/11/30 14:42:13 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

static void				init_tcaps_names(const char *tcaps_names[15])
{
	unsigned int	i;

	i = 0;
	tcaps_names[i++] = "nd";
	tcaps_names[i++] = "le";
	tcaps_names[i++] = "do";
	tcaps_names[i++] = "up";
	tcaps_names[i++] = "dc";
	tcaps_names[i++] = "cl";
	tcaps_names[i++] = "md";
	tcaps_names[i++] = "me";
	tcaps_names[i++] = "cr";
	tcaps_names[i++] = "cd";
	tcaps_names[i++] = "dl";
	tcaps_names[i++] = "al";
	tcaps_names[i++] = "us";
	tcaps_names[i++] = "mr";
	tcaps_names[i++] = "ue";
}

/*
**	Initialize some termcaps that will be used for the shell internal behavior.
*/

struct s_le_termcaps	*init_termcaps_strings(void)
{
	static struct s_le_termcaps tc;
	const char					**index;
	unsigned int				i;
	const char					*tcaps_names[15];
	ptrdiff_t					sizeof_tc;

	sizeof_tc = sizeof(tc);
	init_tcaps_names(tcaps_names);
	index = (const char **)(&tc);
	i = 0;
	while ((ptrdiff_t)((uintptr_t)index - (uintptr_t)(&tc)) < sizeof_tc)
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
