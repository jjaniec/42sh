/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_char_expansion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 16:38:44 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/20 18:50:49 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static char	*get_env_var_value(char *ptr, char **env, int *expansion_name_len)
{
	char	*exp_end_ptr;
	char	exp_end_ptr_char;
	char	*env_var_value;

	exp_end_ptr = get_expansion_end(ptr);
	exp_end_ptr_char = *(exp_end_ptr);
	(*exp_end_ptr) = '\0';
	*expansion_name_len = ft_strlen(ptr);
	env_var_value = get_env(ptr, (const char **)env);
	log_trace("Got env var value of |%s| for %s", env_var_value, ptr);
	*(exp_end_ptr) = exp_end_ptr_char;
	return (env_var_value);
}

void		handle_dollar_expansion(t_lexeme_data_to_clean *l, char **env)
{
	char	*env_var_value;
	int		expansion_name_len;
	char	*new_expansed_data;
	size_t	env_var_value_len;

	env_var_value = get_env_var_value(*(l->raw_lexeme_read_ptr) + 1, env, &expansion_name_len);
	if (env_var_value)
	{
		env_var_value = ft_strdup(env_var_value);
		env_var_value_len = ft_strlen(env_var_value);
		l->new_data_size += env_var_value_len;
		new_expansed_data = malloc(l->new_data_size);

		ft_strcpy(new_expansed_data, l->new_data);
		ft_strcpy(new_expansed_data + (l->new_data_write_ptr - l->new_data), env_var_value);

		l->new_data_write_ptr = \
			(l->new_data_write_ptr - l->new_data) + new_expansed_data + env_var_value_len;
		free(l->new_data);
		l->new_data = new_expansed_data;
		free(env_var_value);
	}
	(*(l->raw_lexeme_read_ptr)) += (expansion_name_len + 1) * sizeof(char);
}
