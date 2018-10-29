/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prompt_details.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <cgaspart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 14:02:16 by cgaspart          #+#    #+#             */
/*   Updated: 2018/10/29 18:57:29 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

static t_prompt	*prompt_setup(void)
{
	t_prompt		*prompt;
	t_shell_vars	*vars;

	prompt = NULL;
	vars = get_shell_vars();
	if (vars->env->get_var(vars->env, "PWD"))
	{
		prompt = (t_prompt*)ft_xmalloc(sizeof(t_prompt));
		prompt->pwd = vars->env->last_used_elem->val_begin_ptr;
		if (vars->env->get_var(vars->env, "HOME"))
			prompt->home = vars->env->last_used_elem->val_begin_ptr;
	}
	return (prompt);
}

void			print_prompt_details(void)
{
	t_prompt	*prompt;
	int			i;

	prompt = prompt_setup();
	ft_putstr(PROMPT_PWD);
	if (!prompt || !prompt->pwd)
		return ;
	i = ft_strlen(prompt->home);
	if (i && !ft_strncmp(prompt->home, prompt->pwd, i))
	{
		ft_putchar('~');
		ft_putstr(&prompt->pwd[i]);
	}
	else
		ft_putstr(prompt->pwd);
	ft_putstr(COL_DEFAULT);
	tputs(access_le_main_datas()->tcaps->_do, 1, &write_one_char);
}
