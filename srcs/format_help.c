/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 18:59:24 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/27 16:32:54 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

void	format_help(char *usage_str, t_option *opts)
{
	t_option	*cur_opt;
	int			cur_opt_name_index;

	ft_printf("   Usage:{FG_RED}\t%s{FG_DEFAULT}\n", usage_str);
	cur_opt = opts;
	while (cur_opt && cur_opt->opt_desc)
	{
		if (cur_opt->opt_name[0][0] == '\n')
			ft_printf("\t%s", cur_opt->opt_name[0] + 1);
		else
			ft_printf("\t-%s", cur_opt->opt_name[0]);
		cur_opt_name_index = 1;
		while (cur_opt_name_index < MAX_OPT_NAMES && \
			cur_opt->opt_name[cur_opt_name_index])
			ft_printf(", -%s", cur_opt->opt_name[cur_opt_name_index++]);
		ft_printf("\t%s\n", cur_opt->opt_desc);
		cur_opt += 1;
	}
}
