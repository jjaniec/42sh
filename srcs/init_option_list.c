/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_option_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 21:15:13 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/11 14:23:51 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static t_option		init_opt(char *opt_name, char *opt_desc, bool activated_by_default)
{
	t_option	opt;

	opt.opt_name = opt_name;
	opt.opt_desc = opt_desc;
	opt.opt_status = activated_by_default;
	return opt;
}

/*
** Store in option tab $opt_tab, 3 next variadic arguments passed as parameters in
** a struct created in init_opt()
*/

void				init_option_list(t_option **opt_tab, ...)
{
	t_option	*ptr;
	va_list		va_ptr;
	char		**tmp;

	ptr = *opt_tab;
	va_start(va_ptr, opt_tab);
	while (1)
	{
		if (!(tmp = va_arg(va_ptr, char **)) || !(*tmp))
			break ;
		*ptr = init_opt(*tmp, va_arg(va_ptr, char *), va_arg(va_ptr, int));
		ptr++;
	}
	//ptr = NULL;
	*ptr = (t_option){NULL, NULL, false};
	va_end(va_ptr);
}
