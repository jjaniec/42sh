/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 16:29:25 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/28 20:17:18 by cyfermie         ###   ########.fr       */
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


static int		read_key(char key[LE_KEY_SIZE])
{
	ssize_t read_ret;

//le_debug("%s", "- - - - - - - READ FUNC\n");
	errno = 0;
	read_ret = read(STDIN_FILENO, key, LE_KEY_SIZE - 1);

	if (errno == EINTR)
	{
		if (g_cmd_status.resize_happened == true
		&& access_le_main_datas()->le_state.prompt_type != LE_DEFAULT_PROMPT)
		{
			g_cmd_status.resize_happened = false;
			return (2);
		}

le_debug("%s", " - - - - - RETURN ZERO\n");
		return 0;
	}

	if (read_ret == -1)
	{
		write(STDERR_FILENO, "\nError while reading on stdin\n", 30);
		perror("read() - perror() report");
	}
return 1;
	// check les differentes erreurs de read(), une coupure a cause d'un signal ...
}

static t_kno	get_key_number(const char *key)
{
	t_kno	key_no;
	t_kno	i;

	key_no = 0;
	i = 0;
	while (i < LE_KEY_SIZE)
	{
		key_no += ((t_kno)key[i]) << i;
		++i;
	}
	return (key_no);
}

char			*line_edition(int prompt_type)
{
	char					*final_line;
	char					key[LE_KEY_SIZE];
	static struct s_line	*le;
	t_kno					key_no;

	le = access_le_main_datas();
	set_term_attr(LE_SET_NEW);
	init_line_edition_attributes(le, prompt_type);
	g_cmd_status.cmd_running = false;

if (g_cmd_status.keep_le_main_datas != NULL)
{
	char *updated_cmd;

		//tputs(access_le_main_datas()->tcaps->cl, 1, write_one_char);
	le_debug("%s", "WINCH REWRITE\n");
		
		//char *new_cmd = ft_strdup(g_cmd_status.keep->cmd);

		if (le->le_state.opt_colosyn == false)
		{
			free(le->cmd); // alloc done in init_le_attributes();
			memcpy( le, g_cmd_status.keep_le_main_datas, sizeof(struct s_line) );
		}
		else
			updated_cmd = ft_strdup(g_cmd_status.keep_le_main_datas->cmd); // check

		free(g_cmd_status.keep_le_main_datas);
		g_cmd_status.keep_le_main_datas = NULL;

		//prompt_show(g_prompts[/*-prompt_type*/ -(g_cmd_status.keep_prompt_type)]);

	le->term_line_size = get_terminal_nb_col();

		if (le->le_state.opt_colosyn == false)
		{
			int tmp_pos = 0;
			for (int i = 0 ; i < (int)le->cmd_len ; ++i)
			{
				if (tmp_pos == (int)le->term_line_size - 1)
				{
					tputs(le->tcaps->_do, 1, write_one_char);
					cursor_crosses_screen(le, CROSS_TO_LEFT);
				}
				print_key(le->cmd[i]);
				//le_debug("WINCH REWRITE PRINT |%c|\n", le->cmd[i]);
			}
		}
		else
		{
			//char *updated_cmd = ft_strdup(le->cmd); // check
			refresh_colosyn(le, updated_cmd);
			free(updated_cmd);
		}


	le_debug("%s", "WINCH REWRITE END\n");
}

struct sigaction new;
sigfillset(&(new.sa_mask));
new.sa_flags = 0;
new.sa_handler = handle_sigwinch;
sigaction(SIGWINCH, &new, NULL);

	le_debug_infos(); // debug
	while ("cest ta merge la jjaniec")
	{
		ft_memset(key, '\0', LE_KEY_SIZE);
		int ret = read_key(key); 
		
		if (ret == 0)
		{
			new.sa_handler = SIG_DFL;
			sigaction(SIGWINCH, &new, NULL);
			set_term_attr(LE_SET_OLD);
			return NULL;
		}
		else if (ret == 2)
		{
			le_debug("%s", "READ EINTR 2\n");
			//free(le->cmd);
			set_term_attr(LE_SET_OLD);
			return (RESIZE_IN_PROGRESS);
		}

		//for (int i = 0 ; key[i] ; ++i) printf("pp = %d||\n", key[i]);
		key_no = get_key_number(key);

		//if (key_no >= 32 && key_no >= 126)
			//fprintf(tty_debug, "key = %" PRIu64 "\n" , key_no); // debug

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
	free(le->cmd);
	le->cmd = NULL;
new.sa_handler = SIG_DFL;
sigaction(SIGWINCH, &new, NULL);

le_debug("%s", "END LE\n");
	return (final_line);
}
