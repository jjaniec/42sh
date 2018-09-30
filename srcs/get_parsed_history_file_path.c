/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parsed_history_file_path.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 17:34:00 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/28 17:34:02 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

char	*get_parsed_history_file_path(void)
{
	static bool		already_done = false;
	static char		*parsed_path = NULL;

	if (!already_done)
	{
		already_done = true;
		parsed_path = ft_strdup(HISTORY_FILE_PATH);
  //  printf("LOL PTDR |%s|\n", parsed_path);
		handle_quotes_expansions(&parsed_path);

   // printf("LOL PTDR |%s|\n", parsed_path);
	}
	return (parsed_path);
}
