/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prompt_details.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <cgaspart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 14:02:16 by cgaspart          #+#    #+#             */
/*   Updated: 2018/10/30 17:07:39 by cgaspart         ###   ########.fr       */
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

/*static int		prompt_len();

int				prompt_show(const char *prompt)
{
	// waiting for the full prompt
	if (prompt == g_prompts[0])
	{
		print_prompt_details();
		ft_putstr(PROMPT_COLOR);
	}
	tputs(access_le_main_datas()->tcaps->md, 1, &write_one_char);
	ft_putstr(prompt);
	if (prompt != g_prompts[0])
	{
		ft_putstr(PROMPT_COLOR);
		ft_putstr(g_prompts[0]);
		return (ft_strlen(prompt) + ft_strlen(g_prompts[0]));
		ft_putstr(COL_DEFAULT);
		tputs(access_le_main_datas()->tcaps->me, 1, &write_one_char);
	}
	else
		return (ft_strlen(g_prompts[0]));
}*/

void			print_prompt_details(void)
{
	t_prompt	*prompt;
	int			i;

	prompt = prompt_setup();
	ft_putstr("\n"PROMPT_PWD);
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
	free(prompt);
	ft_putstr(COL_DEFAULT);
	print_git_info(get_shell_vars()->env->environ);
	tputs(access_le_main_datas()->tcaps->_do, 1, &write_one_char);
}
