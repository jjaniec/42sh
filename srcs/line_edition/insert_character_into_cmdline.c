/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_character_into_cmdline.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 18:29:52 by cyfermie          #+#    #+#             */
/*   Updated: 2018/07/12 19:58:56 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

static void	insert_char_into_array(char *line, t_kno key, unsigned int pos)
{
	// check depassement tableau

	fprintf(tty_debug, "BEFORE LINE = |%s|\n", line);

	fprintf(tty_debug, "je bouge |%s|\n",   line + pos );

	ft_memmove(line + pos + 1, line + pos, ft_strlen(line + pos) );

	line[pos] = key;

	fprintf(tty_debug, "AFTER LINE  = |%s|\n", line);
}

void		insert_character_into_cmdline(struct s_line *le, t_kno key)
{
	//fprintf(tty_debug, "INSERTION CARACTERE A LA POS %u\n", le->cursor_index_for_line);

	unsigned int	keep_pos;
	unsigned int	keep_line;
	unsigned int	keep_cursor_index_for_line;

	keep_pos = le->current_cursor_pos;
	keep_line = le->current_cursor_line;
	keep_cursor_index_for_line = le->cursor_index_for_line;
	
										
	insert_char_into_array(le->line, key, le->cursor_index_for_line);
	++(le->line_index);

	le->nb_li_currently_writing = le->current_cursor_line + 1;
	le->line_index = le->cursor_index_for_line;

	if (le->current_cursor_line == 0)
	{
		le->nb_car_written_on_last_current_line = le->cursor_index_for_line;
	}
	else
	{
		le->nb_car_written_on_last_current_line = le->current_cursor_pos;
	}

	fprintf(tty_debug, "current cursor pos ----- %u\n", le->current_cursor_pos);
	fprintf(tty_debug, "1 ----- %u %u\n", le->current_cursor_line, keep_line);

unsigned int x = le->cursor_index_for_line;
char * _line = le->line;
	while ( _line[x] != '\0' )
	{
		fprintf(tty_debug, "PRINT %c\n", _line[x]);
		print_key_at_end(le, _line[x]);
		++x;
	}

	if (  keep_pos == le->li_max_size - 1   )
		keep_line ++;

	fprintf(tty_debug, "2 ----- %u %u\n", le->current_cursor_line, keep_line);
	int foo = 0;
	int foo2 = 0;
	while (1&&    le->current_cursor_line > keep_line)
	{	//foo = 1;

		//if (  keep_pos == le->li_max_size - 1   )
		//	{ fprintf(tty_debug, "BREAK BREAK\n"); break ; }

		fprintf(tty_debug, "MONTE %u %u\n", keep_pos, le->li_max_size);
		tputs(le->tcaps->up, 1, &write_one_char);
		--(le->current_cursor_line);
		le->cursor_index_for_line -= le->li_max_size - 0;
	}

	
	//sleep(5);

	if (keep_pos == le->li_max_size - 1)
		{ fprintf(tty_debug, "CE IF\n");   keep_pos = 0; foo = 1; }

	fprintf(tty_debug, "while %u %u\n", le->current_cursor_pos, keep_pos );

	while (
	(le->current_cursor_pos - ( (le->current_cursor_pos != 0) ? 1 : 0   )) 
	> keep_pos
	)
		{  /*fprintf(tty_debug, "left\n");*/ actionk_cursor_move_left(le); foo2 = 1; }


	if (foo) actionk_cursor_move_left(le);

	
	while ( (foo2 == 0) &&  le->current_cursor_pos  < ( keep_pos + 1 )     )
		{ /*fprintf(tty_debug, "right\n");*/ 
			
			//if (  foo && (le->current_cursor_pos == le->li_max_size - 1)   )
			//	{ fprintf(tty_debug, "BREAK\n");  break ; }

			actionk_cursor_move_right(le); 
		
		}

}

void		_insert_character_into_cmdline(struct s_line *le, t_kno key)
{
	//fprintf(tty_debug, "INSERTION CARACTERE A LA POS %u\n", le->cursor_index_for_line);

	/* FAUT OPTI CA, CEST TROP LENT CA SE VOIT TROP, PAS BESOIN DE REECRIRE LES CAR QUI
	NE BOUGERONT PAS, CEST A DIRE CEUX QUI PRECEDENT LA POSITION D'INSERTION  
	LE DEFI VA DONC ETRE DE CORRECTEMENT SET - RESET MES VARIABLES DANS struct s_line *le  */

	unsigned int	keep_pos;
	char			tmp[LE_LINE_SIZE];
	unsigned int	len_tmp;
	char			save_clipboard[LE_LINE_SIZE];
	unsigned int	i;

	insert_char_into_array(le->line, key, le->cursor_index_for_line);
	++(le->line_index);
	keep_pos = le->cursor_index_for_line;
	actionk_move_cursor_start(le);
	ft_strcpy(tmp, le->line);
	len_tmp = le->line_index;
	ft_strcpy(save_clipboard, le->clipboard);
	init_line_edition_attributes(le);
	ft_strcpy(le->clipboard, save_clipboard);
	i = 0;
	while (i < len_tmp)
	{
		print_key_at_end(le, tmp[i]);
		++i;
	}
	while ((le->cursor_index_for_line - 1) != keep_pos)
		actionk_cursor_move_left(le);
}
