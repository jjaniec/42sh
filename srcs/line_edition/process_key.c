/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 16:51:50 by cyfermie          #+#    #+#             */
/*   Updated: 2018/06/23 17:53:47 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

static bool    key_is_printable(const char *key)
{
    if (ft_strlen(key) != 1U)
        return (false);
    if (key[0] >= 32 && key[0] <= 126)
        return (true);
    return (false);
}

static void    print_key(char key)
{
    if (write(STDOUT_FILENO, &key, sizeof(char)) == -1)
        le_exit("Writing on stdout failed\n", "write");
}

void            process_key(const char *key)
{
    if (key_is_printable(key))
    {
        print_key(key[0]);
    }
    else
    {
        action_key(key);
    }
}
