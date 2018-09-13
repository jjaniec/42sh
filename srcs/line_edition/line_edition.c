/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 16:29:25 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/06 19:18:08 by cyfermie         ###   ########.fr       */
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
	struct s_line	le = *( access_le_main_datas() );

	fprintf(tty_debug, "--------------------------------------\n");
	fprintf(tty_debug, "line = |%s|\n", le.line);
	fprintf(tty_debug, "line size = %zu\n", le.line_size);
	fprintf(tty_debug, "line index = %u\n", le.line_index);
	fprintf(tty_debug, "cursor index for line = %u - %c\n", \
	le.cursor_index_for_line, le.line[le.cursor_index_for_line]);
	fprintf(tty_debug, "start pos = %u\n", le.start_pos);
	fprintf(tty_debug, "current cursor pos = %u\ncurrent cursor line = %u\n", \
	le.current_cursor_pos, le.current_cursor_line);
	fprintf(tty_debug, "term line size = %zu\n", le.term_line_size);
	fprintf(tty_debug, "nb li currently writing = %u\n", le.nb_li_currently_writing);
	fprintf(tty_debug, "nb_car_written_on_last_current_line = %u\n", \
	le.nb_car_written_on_last_current_line);
	fprintf(tty_debug, "clipboard = |%s|\n", le.clipboard);
	fprintf(tty_debug, "clipboard size = %zu\nclipboard len = %zu\n", \
	le.clipboard_size, le.clipboard_len);
	fprintf(tty_debug, "--------------------------------------\n");
}


static void		read_key(char key[LE_KEY_SIZE])
{
	ssize_t read_ret;

	read_ret = read(STDIN_FILENO, key, LE_KEY_SIZE - 1);
	if (read_ret == -1)
	{
		write(STDERR_FILENO, "\nError while reading on stdin\n", 30);
		perror("read() - perror() report");
	}

	// if (read_ret == 0) ?  ctrl + d causes EOF ? think about that later ... 
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
	//g_le = &le;
	t_kno					key_no;

	le = access_le_main_datas();
	le->le_state.prompt_type = prompt_type; // a mettre au bon endroit xd
	set_term_attr(LE_SET_NEW);
	init_line_edition_attributes(le);

	//le_debug_infos(); // debug

	le_debug_infos(); // debug
	while ("cest ta mere la jjaniec")
	{
		ft_memset(key, '\0', LE_KEY_SIZE);
		read_key(key);

		//for (int i = 0 ; key[i] ; ++i) printf("pp = %d||\n", key[i]);
		key_no = get_key_number(key);

		if (key_no >= 32 && key_no >= 126)
			fprintf(tty_debug, "key = %" PRIu64 "\n" , key_no); // debug

		process_key(key_no, le);
		le_debug_infos(); // debug

		if (key_no == '\n')
		{
			set_term_attr(LE_SET_OLD);
			break ;
			// need more things to do in the future when line is finished
		}

	}

	le->special_case_for_newest_his_elem = false;
	actionk_move_cursor_end(le);
	if (le->line[0] != '\0' && le->line[0] != '\n')
		add_history(le);

	reset_history_on_first_elem(le);

	if ((final_line = ft_strdup(le->line)) == NULL)
		le_exit("Memory allocation failed\n", "malloc", errno);
	free(le->line);
	return (final_line);

	/*
		En fait faudra retourner une structure qui contient la commande,
		mais aussi peut etre des codes d'erreur pour remplacer le_exit(),
		c'est à discuter avec les collegues.
		Il faudra aussi dans la structure, un pointeur vers l'historique
		pour pouvoir le free() si necessaire et le save dans un fichier ...
	*/
}


////////////////////////////////////////////////////////////// for tests
/*
void	prompt(void)
{
	printf("PROMPT  $> ");
	fflush(stdout);
}
*/

/*
void	prepare_test(void)
{
	tty_debug = fopen(TTY_DEBUG, "w");
	if (tty_debug == NULL)
	{
		perror("perror report - fopen() failed in prepare_test()");
		exit(123);
	}
}
*/

/*
int	 main(void)
{
	char	*input;

	prepare_test();
	
	while ("\x1b\x5b\x48\x1b\x5b\x32\x4a\x00\x66\x75\x63\x6b")
	{
		prompt();
		
		input = line_edition();
		//printf("\ninput = |%s|\n", s);
		
		if ( strcmp(input, "q\n") == 0 )
			break ;
		
		//printf("\nINPUT = |%s|", input);

		free(input);

#define TERPRI putchar('\n')
		if (TERPRI, TERPRI, TERPRI)
			;
	}
	
	fclose(tty_debug);

	return
	!!!!!!!!!!!!! 
	"patate + licorne = patatorne"
	+ !!!
	TERPRI
	;;;
}*/