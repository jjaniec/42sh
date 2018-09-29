/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 16:29:25 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/29 20:03:27 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // debug
FILE *tty_debug = NULL; // debug
#define FOOLOL // debug


#include <twenty_one_sh.h>
#undef FOOLOL // debug

// debug function
static void		le_debug_infos(void)
{
	struct s_line	*le = access_le_main_datas();

	le_debug("%s", "--------------------------------------\n");
	le_debug("PID du 42sh = %d\n", (int)getpid());
	le_debug("key number = %llu\n", (unsigned long long)(le->key_no));
	le_debug("cmd = |%s|\n", le->cmd);
	le_debug("cmd size = %zu\n", le->cmd_size);
	le_debug("cmd len = %zu\n", le->cmd_len);
	le_debug("cursor index = %u - %c\n", \
	le->cursor_index, le->cmd[le->cursor_index]);
	le_debug("start pos = %u\n", le->start_pos);
	le_debug("cursor pos = %u\ncursor line = %u\n", \
	le->cursor_pos, le->cursor_line);
	le_debug("term line size = %zu\n", le->term_line_size);
	le_debug("nb lines written = %u\n", le->nb_lines_written);
	le_debug("nb char on last line = %u\n", \
	le->nb_char_on_last_line);
	le_debug("clipboard = |%s|\n", le->clipboard);
	le_debug("clipboard size = %zu\nclipboard len = %zu\n", \
	le->clipboard_size, le->clipboard_len);
	le_debug("save tmp cmd = |%s|\n", le->save_tmp_cmd);
	le_debug("%s","--------------------------------------\n");
}


static int		read_key(char key[LE_KEY_BUFFER_SIZE])
{
	ssize_t read_ret;

	errno = 0;
	read_ret = read(STDIN_FILENO, key, LE_KEY_BUFFER_SIZE - 1);
	if (errno == EINTR)
	{
		if (g_cmd_status.resize_happened == true
		&& access_le_main_datas()->le_state.prompt_type != LE_DEFAULT_PROMPT)
			return (2);
		return (0);
	}
	if (read_ret == -1)
		le_exit("\nfatal error while reading on stdin\n", "read", errno);
	return (1);
}

static t_kno	get_key_number(const char *key)
{
	t_kno	key_no;
	t_kno	i;

	key_no = 0;
	i = 0;
	while (i < LE_KEY_BUFFER_SIZE)
	{
		key_no += ((t_kno)key[i]) << i;
		++i;
	}
	return (key_no);
}

static struct s_line	*prepare_line_edition(int prompt_type, \
											  struct sigaction *le_sig)
{
	struct s_line		*le;

	le = access_le_main_datas();
	set_term_attr(LE_SET_NEW);
	init_line_edition_attributes(le, prompt_type);
	g_cmd_status.cmd_running = false;

	if (g_cmd_status.resize_happened == true)
		handle_window_resize(le);

	sigfillset(&(le_sig->sa_mask));
	le_sig->sa_flags = 0;
	le_sig->sa_handler = &(handle_sigwinch);
	sigaction(SIGWINCH, le_sig, NULL);
	return (le);
}

char			*line_edition(int prompt_type)
{
	char					*final_line;
	static struct s_line	*le;
	t_kno					key_no;
	struct sigaction		le_sig;
	

	le = prepare_line_edition(prompt_type, &le_sig);

	le_debug_infos(); // debug
	while ("cest ta merge la jjaniec")
	{
		ft_memset(le->key_buffer, '\0', LE_KEY_BUFFER_SIZE);
		int ret = read_key(le->key_buffer); 
		
		if (ret == 0)
		{
			le_sig.sa_handler = SIG_DFL;
			sigaction(SIGWINCH, &le_sig, NULL);
			set_term_attr(LE_SET_OLD);
			return (NULL);
		}
		else if (ret == 2)
		{
			set_term_attr(LE_SET_OLD);
			return (RESIZE_IN_PROGRESS);
		}

		//for (int i = 0 ; key[i] ; ++i) printf("pp = %d||\n", key[i]);
		key_no = get_key_number(le->key_buffer);

		process_key(key_no, le);
		le_debug_infos(); // debug

		if (key_no == '\n')
		{
			set_term_attr(LE_SET_OLD);
			break ;
		}
	}

	actionk_move_cursor_end(le);
	reset_history_on_first_elem(le);

	if ((final_line = ft_strdup(le->cmd)) == NULL)
		le_exit("Memory allocation failed\n", "malloc", errno);
	free(le->cmd); // or ft_memdel(&(le->cmd));
	le->cmd = NULL;

le_sig.sa_handler = SIG_DFL;
sigaction(SIGWINCH, &le_sig, NULL);

	return (final_line);
}
