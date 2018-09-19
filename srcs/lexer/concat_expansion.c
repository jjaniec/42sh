/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concat_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 16:38:06 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/19 19:41:05 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

char		*concat_expansion(char *exp_begin_ptr, char *exp_end_ptr, \
				char *exp_val, char *lex_data)
{
	char	*new_data_str;
	char	*new_data_str_cpyptr;
	char	*ptr;


	new_data_str = malloc((ft_strlen(lex_data) - \
		((exp_end_ptr - exp_begin_ptr) * sizeof(char)) + ft_strlen(exp_val) + 1) * 5);
	new_data_str_cpyptr = new_data_str;
	ptr = lex_data;
	while (ptr && ptr != exp_begin_ptr && *ptr)
		*(new_data_str_cpyptr++) = *(ptr++);
	if (exp_val && *exp_val)
	{
		ptr = exp_val;
		while (ptr && *ptr)
			*(new_data_str_cpyptr++) = *(ptr++);
	}
	ptr = exp_end_ptr;
	while (ptr && *ptr)
		*(new_data_str_cpyptr++) = *(ptr++);
	*(new_data_str_cpyptr++) = '\0';
	return (new_data_str);
/*
	ft_strncpy(new_data_str, lex_data, (exp_begin_ptr - lex_data) * sizeof(char));
	ft_strcpy(new_data_str + ((exp_begin_ptr - lex_data) * sizeof(char)), exp_val);
	ft_strcpy(new_data_str + ((exp_begin_ptr - lex_data) * sizeof(char)) \
		+ ft_strlen(lex_data), exp_end_ptr);*/
	

	/*
	char	*expansion_prefix_data;
	char	*expansion_suffix_data;
	char	*ret;
	char	*ptr;
	int		i;
	int		new_string_len;

	expansion_prefix_data = lexeme->data;
	log_debug("exp prefix data %s", expansion_prefix_data);
	expansion_suffix_data = get_expansion_end(expansion_char_pos, lexeme->lexeme_end_ptr);
	log_debug("exp suffix data %s", expansion_suffix_data);

	new_string_len = ft_strlen(lexeme->data) - \
		ft_strlen(expansion_char_pos) + ((env_val) ? (ft_strlen(env_val)) : (0)) + 1;
	ret = malloc(sizeof(char) * new_string_len * 5);
	ptr = expansion_prefix_data;
	i = 0;
	//expansion_pos_in_data
	log_info("exp pos in data : %s", expansion_char_pos);
	while (ptr && *ptr && *ptr != *expansion_char_pos)
		ret[i++] = *(ptr++);
	//log_info("Stop 1st while %s", ret);
	while (env_val && *env_val)
		ret[i++] = *(env_val++);
	ptr = expansion_suffix_data;
	while (ptr && *ptr)
		ret[i++] = *(ptr++);
	ret[i] = '\0';
	return (ret);*/
}
