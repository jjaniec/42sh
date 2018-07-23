/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfermier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 14:42:58 by cfermier          #+#    #+#             */
/*   Updated: 2018/07/23 14:42:58 by cfermier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

void    print_key(t_kno key)
{
    if (write(STDOUT_FILENO, &key, sizeof(char)) != sizeof(char))
		  le_exit("Writing on stdout failed\n", "write");
}
