/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parsed_42shrc_path.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 20:45:53 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/26 21:18:48 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

char  *get_parsed_42shrc_path(void)
{
    static bool         already_done = false;
    static char   *parsed_path = NULL;

    if (!already_done)
    {
        already_done = true;
        parsed_path = ft_strdup(_42SHRC_PATH);
  //  printf("LOL PTDR |%s|\n", parsed_path);
        handle_quotes_expansions(&parsed_path);

   // printf("LOL PTDR |%s|\n", parsed_path);
    }
    return (parsed_path);
}
