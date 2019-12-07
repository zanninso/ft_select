/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:44:12 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/12/07 02:54:19 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void up_cursor(t_ft_select *ft_select)
{
	const int old_cursor_position = ft_select->cursor;

	ft_select->cursor += ft_select->count - 1;
	ft_select->cursor %= ft_select->count;
	cursor_move(ft_select, old_cursor_position);
}

void down_cursor(t_ft_select *ft_select)
{
	const int old_cursor_position = ft_select->cursor;

	ft_select->cursor += 1;
	ft_select->cursor %= ft_select->count;
	cursor_move(ft_select, old_cursor_position);
}

void select_item(t_ft_select *ft_select)
{
	ft_select->items[ft_select->cursor].selected ^= 1;
	if (ft_select->items[ft_select->cursor].selected)
		tputs(tgetstr("mr", 0), 0, output);
	tputs(tgoto(tgetstr("cm", 0), 0, ft_select->cursor), 0, output);
	ft_putstr_fd(ft_select->items[ft_select->cursor].content, ft_select->fd);
	tputs(tgetstr("me", 0), 0, output);
	down_cursor(ft_select);
}

void delete_item(t_ft_select *ft_select)
{
	const int count = ft_select->count - 1;
	const int cursor = ft_select->cursor;

	t_item *items;
	if (count == 0)
		end(ft_select);
	items = ft_select->items;
	tputs(tgoto(tgetstr("cm", 0), 0, ft_select->cursor), 0, output);
	tputs(tgetstr("cd", 0), 0, output);
	ft_select->count--;
	if (cursor < ft_select->count)
	{
		ft_memcpy(&items[cursor], &items[cursor + 1], sizeof(t_item) * (count - cursor));
		print_args(ft_select);
	}
	else
	{
		ft_select->cursor--;
		print_args(ft_select);
	}
}

void end(t_ft_select *ft_select)
{
	int i;

	i = 0;
	tputs(tgetstr("te", 0), 0, output);
	while (i < ft_select->count)
	{
		if (ft_select->items[i].selected)
			ft_putendl_fd(ft_select->items[i].content, 0);
		i++;
	}
	tputs(tgetstr("ve", 0), 0, output);
	exit(0);
}