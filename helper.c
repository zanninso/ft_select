/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:44:38 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/12/07 01:05:28 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void cursor_move(t_ft_select *ft_select, int old_cursor_position)
{
	if (ft_select->items[old_cursor_position].selected)
		tputs(tgetstr("mr", 0), 0, output);
	tputs(tgoto(tgetstr("cm", 0), 0, old_cursor_position), 0, output);
	ft_putstr_fd(ft_select->items[old_cursor_position].content, ft_select->fd);
	tputs(tgetstr("me", 0), 0, output);
	if (ft_select->items[ft_select->cursor].selected)
		tputs(tgetstr("mr", 0), 0, output);
	tputs(tgetstr("us", 0), 0, output);
	tputs(tgoto(tgetstr("cm", 0), 0, ft_select->cursor), 0, output);
	ft_putstr_fd(ft_select->items[ft_select->cursor].content, ft_select->fd);
	tputs(tgetstr("me", 0), 0, output);
}

int output(int str)
{
	static int fd;

	if (str > 255)
		fd = str - 255;
	else
		write(fd, &str, 1);
	return (0);
}

void print_args(t_ft_select *ft_select)
{
	int i;

	i = ft_select->cursor;
	while (i < ft_select->count)
	{
		if (ft_select->items[i].selected)
			tputs(tgetstr("mr", 0), 0, output);
		if(i == ft_select->cursor)
			tputs(tgetstr("us", 0), 0, output);
		tputs(tgoto(tgetstr("cm", 0), 0, i), 0, output);
		ft_putstr_fd(ft_select->items[i].content, ft_select->fd);
		tputs(tgetstr("me", 0), 0, output);
		i++;
	}
}