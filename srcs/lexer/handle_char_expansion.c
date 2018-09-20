/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_char_expansion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 16:38:44 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/20 19:18:56 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Return environnement variable value of expansion beginning at $ptr
*/

static char		*get_env_var_value(char *ptr, char **env, int *expansion_name_len)
{
	char	*exp_end_ptr;
	char	exp_end_ptr_char;
	char	*env_var_value;

	exp_end_ptr = get_expansion_end(ptr);
	exp_end_ptr_char = *(exp_end_ptr);
	(*exp_end_ptr) = '\0';
	*expansion_name_len = ft_strlen(ptr);
	env_var_value = get_env(ptr, (const char **)env);
	log_trace("Got env var value of |%s| for %s env variable expansion", env_var_value, ptr);
	*(exp_end_ptr) = exp_end_ptr_char;
	return (env_var_value);
}

/*
** Concat data of l->new_data and expansion variable value
** in the new string that will substitute l->new_data
*/

static void		concat_expansion_data(t_lexeme_clean_data *l, char *expansion_value)
{
	size_t	expansion_value_len;
	char	*new_data_str;
	int		write_ptr_offset;

	expansion_value_len = ft_strlen(expansion_value);
	l->clean_data_size += expansion_value_len;
	new_data_str = malloc(l->clean_data_size);
	ft_strcpy(new_data_str, l->clean_data);
	write_ptr_offset = (l->clean_data_write_ptr - l->clean_data) * sizeof(char);
	ft_strcpy(new_data_str + write_ptr_offset, expansion_value);
	l->clean_data_write_ptr = \
		write_ptr_offset + new_data_str + expansion_value_len;
	free(l->clean_data);
	l->clean_data = new_data_str;
}

/*
** Remakes l->new_data string w/ expansed environnement variable
** and replace new_data_write_ptr pointer to use the new malloced string
** w/ substitute_data()
*/

void			handle_dollar_expansion(t_lexeme_clean_data *l, char **env)
{
	char	*env_var_value;
	int		expansion_name_len;

	env_var_value = get_env_var_value(*(l->raw_lexeme_read_ptr) + 1, env, &expansion_name_len);
	if (env_var_value && *env_var_value)
		concat_expansion_data(l, env_var_value);
	else
		free(env_var_value);
	(*(l->raw_lexeme_read_ptr)) += (expansion_name_len + 1) * sizeof(char);
}
