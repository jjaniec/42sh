/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 09:21:39 by cgaspart          #+#    #+#             */
/*   Updated: 2018/09/25 18:24:23 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# define GNL_BUFF_SIZE 1024

typedef struct        s_slot
{
    char            *save;
    int                fd;
    struct s_slot    *next;
}                    t_slot;

int                    get_next_line(const int fd, char **line);

#endif
