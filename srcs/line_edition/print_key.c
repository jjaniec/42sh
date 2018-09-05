/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 14:42:58 by cfermier          #+#    #+#             */
/*   Updated: 2018/09/02 20:52:01 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void    print_key(t_kno key)
{
    if (write(STDOUT_FILENO, &key, sizeof(char)) != sizeof(char))
		  le_exit("Writing on stdout failed\n", "write", errno);
}
