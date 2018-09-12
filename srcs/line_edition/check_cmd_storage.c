/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_storage.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfermier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 16:19:43 by cfermier          #+#    #+#             */
/*   Updated: 2018/09/11 16:19:43 by cfermier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static
void		*ft_realloc(void *ptr, size_t original_size, size_t new_size)
{
	void	*new;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	else if (ptr == NULL)
		return (malloc(new_size));
	if ((new = malloc(new_size)) == NULL)
		return (NULL);
	if (new_size < original_size)
		ft_memcpy(new, ptr, new_size);
	else
		ft_memcpy(new, ptr, original_size);
	free(ptr);
	return (new);
}

void	check_clipboard_storage(struct s_line *le, unsigned int nb_char)
{
	void	*tmp_realloc;

	while (le->clipboard_len + nb_char + 1 >= le->clipboard_size)
	{
		fprintf(tty_debug, "REALLOCATION DE LA MEMOIRE DE L\'ORDINATEUR clipboard\n");
		
		tmp_realloc = ft_realloc(le->clipboard, le->clipboard_size, le->clipboard_size * 2);
		if (tmp_realloc == NULL)
			le_exit("Memory allocation failed\n", "malloc", errno);
		le->clipboard = tmp_realloc;
		le->clipboard_size *= 2;
	}
}

void	check_cmd_storage(struct s_line *le, unsigned int nb_char)
{
	void	*tmp_realloc;

	while (le->line_index + nb_char + 1 >= le->line_size)
	{
		fprintf(tty_debug, "REALLOCATION DE LA MEMOIRE DE L\'ORDINATEUR\n");
		
		tmp_realloc = ft_realloc(le->line, le->line_size, le->line_size * 2);
		if (tmp_realloc == NULL)
			le_exit("Memory allocation failed\n", "malloc", errno);
		le->line = tmp_realloc;
		le->line_size *= 2;
	}
}
