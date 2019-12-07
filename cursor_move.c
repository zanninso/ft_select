/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 06:44:03 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/12/07 08:22:28 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void cursor_move(t_ft_select *ft_select, int old_cursor_position)
{
	int col;
	int line;

	if (ft_select->items[old_cursor_position].selected)
		tputs(tgetstr("mr", 0), 0, output);
	line = old_cursor_position % ft_select->line;
	col = (ft_select->max_len + 1) * (old_cursor_position / ft_select->line);
	tputs(tgoto(tgetstr("cm", 0), col, line), 0, output);
	ft_putstr_fd(ft_select->items[old_cursor_position].content, ft_select->fd);
	tputs(tgetstr("me", 0), 0, output);
	if (ft_select->items[ft_select->cursor].selected)
		tputs(tgetstr("mr", 0), 0, output);
	tputs(tgetstr("us", 0), 0, output);
	line = ft_select->cursor % ft_select->line;
	col = (ft_select->max_len + 1) * (ft_select->cursor / ft_select->line);
	tputs(tgoto(tgetstr("cm", 0), col, line), 0, output);
	ft_putstr_fd(ft_select->items[ft_select->cursor].content, ft_select->fd);
	tputs(tgetstr("me", 0), 0, output);
}

void cur_up(t_ft_select *ft_select)
{
	const int old_cursor_position = ft_select->cursor;

	ft_select->cursor += ft_select->count - 1;
	ft_select->cursor %= ft_select->count;
	cursor_move(ft_select, old_cursor_position);
}

void cur_down(t_ft_select *ft_select)
{
	const int old_cursor_position = ft_select->cursor;

	ft_select->cursor += 1;
	ft_select->cursor %= ft_select->count;
	cursor_move(ft_select, old_cursor_position);
}

void cur_left(t_ft_select *ft_select)
{
	const int old_cursor_position = ft_select->cursor;

	 if (ft_select->cursor < ft_select->line)
		ft_select->cursor = ft_select->count - ft_select->cursor;
	else
		ft_select->cursor += ft_select->count - ft_select->line;
	ft_select->cursor %= ft_select->count;
	cursor_move(ft_select, old_cursor_position);
}

void cur_right(t_ft_select *ft_select)
{
	const int old_cursor_position = ft_select->cursor;

	if (ft_select->cursor + ft_select->line >= ft_select->count)
		ft_select->cursor = ft_select->cursor % ft_select->line;
	else
		ft_select->cursor += ft_select->line;
	ft_select->cursor %= ft_select->count;
	cursor_move(ft_select, old_cursor_position);
}