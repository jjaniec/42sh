/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prompt_details.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <cgaspart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 14:02:16 by cgaspart          #+#    #+#             */
/*   Updated: 2018/10/30 18:42:04 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

static void prompt_setup(t_prompt *prompt)
{
	t_shell_vars	*vars;

	vars = get_shell_vars();
	if (vars->env->get_var(vars->env, "PWD"))
	{
		prompt->pwd = vars->env->last_used_elem->val_begin_ptr;
		if (vars->env->get_var(vars->env, "HOME"))
			prompt->home = vars->env->last_used_elem->val_begin_ptr;
	}
}

static void		print_git_info(char **env)
{
	char	*git_branch_str;
	char	*tmp;

	if (!(git_branch_str = get_git_info(env)))
		return ;
	if (ft_strequ(git_branch_str, "HEAD"))
	{
		free(git_branch_str);
		return ;
	}
	tmp = ft_strjoin(PROMPT_BRANCH_COLOR""PROMPT_BRANCH_PREFIX, git_branch_str);
	free(git_branch_str);
	git_branch_str = ft_strjoin(tmp, COL_DEFAULT);
	free(tmp);
	write(1, git_branch_str, ft_strlen(git_branch_str));
	free(git_branch_str);
}

void			print_prompt_details(void)
{
	t_prompt	prompt;
	int			i;

	prompt_setup(&prompt);
	ft_putstr("\n"PROMPT_PWD);
	if (!prompt.pwd)
		return ;
	i = ft_strlen(prompt.home);
	if (i && !ft_strncmp(prompt.home, prompt.pwd, i))
	{
		ft_putchar('~');
		ft_putstr(&prompt.pwd[i]);
	}
	else
		ft_putstr(prompt.pwd);
	ft_putstr(COL_DEFAULT);
	print_git_info(get_shell_vars()->env->environ);
	tputs(access_le_main_datas()->tcaps->_do, 1, &write_one_char);
}
