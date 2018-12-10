/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_elem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 14:42:31 by jjaniec           #+#    #+#             */
/*   Updated: 2018/02/13 16:25:28 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Handle invalid unicodes in S/ls conversions, when converting the wchar_t *
** into a char *, ft_wchar_tptr_to_str will place a '!' where the invalid
** unicode would be, if the precision specified tell the invalid unicode to
** not be printed, apply the precision, otherwise free the element & return -1
*/

static t_arg	*ft_handle_ls_error(t_arg *e)
{
	int		sprec;
	int		errpos;

	sprec = 0;
	errpos = -1;
	if (e->precision)
	{
		sprec = ft_atoi(e->precision);
		if (e->data_converted)
		{
			while (e->data_converted[++errpos] != '!')
				;
			if (sprec <= errpos)
			{
				e->data_converted[sprec] = '\0';
				ft_apply_options(&e);
				e->next = NULL;
				return (e);
			}
		}
	}
	return (ft_free_elem(e));
}

/*
** Handle unicode error cases w/ C/lc conversions, \
** when a defective unicode is found,
** return an element with data as 'err' (non possible in C/lc conversions)
** and his conversion as "!" to
** let know ft_print_next_arg to stop at previous element & return -1,
** otherwise, free the element and return -1
*/

static t_arg	*ft_handle_lc_error(t_arg *e)
{
	if (*(e->flag) == 'C' || \
		(*(e->flag) == 'c' && (e->modifiers) && *(e->modifiers) == 'l'))
	{
		free(e->data_converted);
		free(e->flag);
		e->data_converted = ft_strdup("err");
		e->flag = ft_strdup("!");
		ft_apply_options(&e);
		e->next = NULL;
		return (e);
	}
	return (ft_free_elem(e));
}

/*
** Check for unicode errors when converting content,
** if none are found, apply options and return element
*/

static t_arg	*ft_handle_errors(t_arg *e)
{
	if (!e->data_converted)
		return (ft_handle_lc_error(e));
	if (e->flag && ft_strchr(e->data_converted, '!') && (*(e->flag) == 'S' || \
		(*(e->flag) == 's' && e->modifiers && *(e->modifiers) == 'l')))
		return (ft_handle_ls_error(e));
	ft_apply_options(&e);
	e->next = NULL;
	return (e);
}

/*
** Create and return an element of type t_arg to store data of an argument
** and all of it's options (precision / width / modifiers / flags)
*/

t_arg			*ft_create_elem(va_list va_ptr, const char *format, \
	int pos)
{
	t_arg	*e;

	e = (t_arg *)malloc(sizeof(t_arg));
	e->attributes = ft_parse_attributes(format, &pos);
	e->width = ft_parse_width(format, &pos);
	if (format[pos + 1] == '.')
		e->precision = ft_parse_precision(format, &pos);
	else
		e->precision = NULL;
	if (format[pos + 1] == 'l' || format[pos + 1] == 'h' || \
		format[pos + 1] == 'z' || format[pos + 1] == 'j')
		e->modifiers = ft_parse_modifiers(format, &pos);
	else
		e->modifiers = NULL;
	e->flag = ft_get_flag(format, pos);
	if (e->modifiers)
		e->data_converted = ft_convert_arg_modifiers(va_ptr, &e);
	else
		e->data_converted = ft_convert_arg_no_modifiers(va_ptr, e->flag[0]);
	return (ft_handle_errors(e));
}
