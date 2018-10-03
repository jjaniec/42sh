/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 14:51:42 by cgaspart          #+#    #+#             */
/*   Updated: 2018/09/25 16:57:15 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

static t_slot    *get_slot(t_slot *first, int fd)
{
    t_slot    *slot;

    slot = first;
    while (slot && slot->fd != fd)
        slot = slot->next;
    if (!slot)
    {
        if (!(slot = malloc(sizeof(t_slot))) ||
        !(slot->save = ft_strnew(0)))
            return (0);
        slot->fd = fd;
        slot->next = NULL;
        while (first && first->next)
            first = first->next;
        if (first)
            first->next = slot;
    }
    return (slot);
}

static int        process_slot(t_slot *slot, char **line)
{
    char    *tmp;
    char    *new;

    if (!(tmp = ft_strdup(slot->save)))
        return (-1);
    free(slot->save);
    if (*tmp == '\n')
    {
        if (!(slot->save = ft_strdup(tmp + 1)) ||
        !(*line = ft_strnew(0)))
            return (-1);
        free(tmp);
        return (1);
    }
    if (!(slot->save = ft_strchr(tmp, '\n') ?
    ft_strdup(ft_strchr(tmp, '\n') + 1) : ft_strnew(0)))
        return (-1);
    if (ft_strchr(tmp, '\n'))
        *ft_strchr(tmp, '\n') = '\0';
    if (!(new = *tmp ? tmp : ft_strnew(0)))
        return (-1);
    *line = new;
    if (new != tmp)
        free(tmp);
    return (*new ? 1 : 0);
}

int                get_next_line(const int fd, char **line)
{
    static t_slot    *first;
    t_slot            *slot;
    int                rd;
    char            buff[GNL_BUFF_SIZE + 1];
    char            *tmp;

    if (!line || !(slot = get_slot(first, fd)))
        return (-1);
    first = first ? first : slot;
    while ((rd = read(fd, buff, GNL_BUFF_SIZE)) && rd != -1)
    {
        buff[rd] = '\0';
        tmp = ft_strjoin(slot->save, buff);
        free(slot->save);
        slot->save = tmp;
        if (ft_strchr(slot->save, '\n'))
            return (process_slot(slot, line));
    }
    return (rd == -1 ? -1 : process_slot(slot, line));
}
