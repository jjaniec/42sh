/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 16:22:54 by cyfermie          #+#    #+#             */
/*   Updated: 2018/11/27 16:28:05 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

static enum e_read_key	get_user_input(char key[LE_KEY_BUFFER_SIZE])
{
	ssize_t read_ret;

	errno = 0;
	read_ret = read(STDIN_FILENO, key, LE_KEY_BUFFER_SIZE - 1);
	if (errno == EINTR)
	{
		if (g_cmd_status.resize_happened == true
		&& access_le_main_datas()->le_state.prompt_type != LE_DEFAULT_PROMPT)
			return (INTR_BY_SIGWINCH);
		return (INTR_BY_SIGINT);
	}
	if (read_ret == -1)
	{
		ft_putstr_fd(SH_NAME ": fatal input error\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	return (ALL_IS_ALRIGHT);
}

char					*read_key(char key[LE_KEY_BUFFER_SIZE],
									struct sigaction *le_sig)
{
	enum e_read_key		ret_user_input;

	ft_memset(key, '\0', LE_KEY_BUFFER_SIZE);
	ret_user_input = get_user_input(key);
	if (ret_user_input == INTR_BY_SIGINT)
	{
		le_sig->sa_handler = SIG_DFL;
		sigaction(SIGWINCH, le_sig, NULL);
		set_term_attr(LE_SET_OLD);
		return (NULL);
	}
	else if (ret_user_input == INTR_BY_SIGWINCH)
	{
		set_term_attr(LE_SET_OLD);
		return (RESIZE_IN_PROGRESS);
	}
	return (key);
}
