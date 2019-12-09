/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 06:44:03 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/12/09 16:26:52 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void cursor_move(t_ft_select *ft_select, int old_cursor, int new_cursor)
{
	ft_select->cursor = new_cursor;
	cur_goto(ft_select, new_cursor);
	active_modes(ft_select, new_cursor);
	ft_putstr_fd(ft_select->items[new_cursor].content, ft_select->fd);
	deactive_modes();
	cur_goto(ft_select, old_cursor);
	active_modes(ft_select, old_cursor);
	ft_putstr_fd(ft_select->items[old_cursor].content, ft_select->fd);
	deactive_modes();
}

void cur_up(t_ft_select *ft_select)
{
	int new_cursor;

	new_cursor = ft_select->cursor + (ft_select->count - 1);
	new_cursor %= ft_select->count;
	cursor_move(ft_select, ft_select->cursor, new_cursor);
}

void cur_down(t_ft_select *ft_select)
{
	int new_cursor;

	new_cursor = ft_select->cursor + 1;
	new_cursor %= ft_select->count;
	cursor_move(ft_select, ft_select->cursor, new_cursor);
}

void cur_left(t_ft_select *ft_select)
{
	int new_cursor;

	if (ft_select->cursor < ft_select->rows_count)
	{
		new_cursor = ft_select->cursor + ft_select->rows_count * (ft_select->max_col - 1);
		if (new_cursor >= ft_select->count)
			new_cursor -= ft_select->rows_count;
	}
	else
		new_cursor = ft_select->cursor + ft_select->count - ft_select->rows_count;
	new_cursor %= ft_select->count;
	cursor_move(ft_select, ft_select->cursor, new_cursor);
}

void cur_right(t_ft_select *ft_select)
{
	int new_cursor;

	if (ft_select->cursor + ft_select->rows_count >= ft_select->count)
		new_cursor = ft_select->cursor % ft_select->rows_count;
	else
		new_cursor = ft_select->cursor + ft_select->rows_count;
	new_cursor %= ft_select->count;
	cursor_move(ft_select, ft_select->cursor, new_cursor);
}
