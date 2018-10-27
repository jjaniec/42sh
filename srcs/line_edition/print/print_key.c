/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 14:42:58 by cfermier          #+#    #+#             */
/*   Updated: 2018/10/20 15:53:20 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**	Print a key in the terminal's window.
*/

void    print_key(t_kno key)
{
    if (write(STDOUT_FILENO, &key, sizeof(char)) != sizeof(char))
    {
		  ft_putstr_fd("Writing on stdout failed\n", 2);
          exit(EXIT_FAILURE);
    }
}
