/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 19:38:32 by sbrucker          #+#    #+#             */
/*   Updated: 2018/12/05 19:20:36 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Main function for printing and showing the tree from the root
*/

void		ast_debug(t_ast *root, int mode)
{
	if (root)
	{
		if (mode)
			print_ast_tree(root, 0);
		else
			print_ast_tree_ugly(root, 0);
	}
}
