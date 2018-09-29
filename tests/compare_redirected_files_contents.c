/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_redirected_files_contents.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 17:38:22 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/29 20:58:41 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void	compare_redirected_files_contents(char *test_name, char *test, char *data_expected)
{
	int		fd;
	char	data_in_file[BUFF_SIZE_TMP_FILE];
	int		tmp;

	system(test);
	fd = open(TESTS_TMP_FILENAME, O_RDONLY);
	if ((tmp = read(fd, data_in_file, BUFF_SIZE_TMP_FILE)) == -1)
	{
		printf("READ ERROR FOR TEST %s\n", test_name);
		return ;
	}
	data_in_file[tmp] = '\0';
	close(fd);
	is(data_in_file, data_expected, test_name);
	remove(TESTS_TMP_FILENAME);
}
