/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_char_expansion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 16:38:44 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/20 13:51:28 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static char	*get_env_var_value(char *ptr, char **env)
{
	char	*exp_end_ptr;
	char	exp_end_ptr_char;
	char	*env_var_value;

	exp_end_ptr = get_expansion_end(ptr);
	exp_end_ptr_char = *(exp_end_ptr);
	(*exp_end_ptr) = '\0';
	env_var_value = get_env(ptr, (const char **)env);
	log_trace("Got env var value of |%s| for %s", env_var_value, ptr);
	*(exp_end_ptr) = exp_end_ptr_char;
	return (env_var_value);
}

void		handle_dollar_expansion(char *exp_char_ptr, char **env, char **s_ptr, char **i_ptr)
{
	(void)exp_char_ptr;
	(void)env;
	(void)s_ptr;
	(void)i_ptr;

	char	*env_var_value;

	env_var_value = get_env_var_value(exp_char_ptr + 1, env);


	*i_ptr += 1;
}
