/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:44:12 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/12/07 13:45:33 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void select_item(t_ft_select *ft_select)
{
	ft_select->items[ft_select->cursor].selected ^= 1;
	if (ft_select->items[ft_select->cursor].selected)
		tputs(tgetstr("mr", 0), 0, output);
	tputs(tgoto(tgetstr("cm", 0), 0, ft_select->cursor), 0, output);
	ft_putstr_fd(ft_select->items[ft_select->cursor].content, ft_select->fd);
	tputs(tgetstr("me", 0), 0, output);
	cur_down(ft_select);
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

void			rediment(void)
{
	struct winsize		wn;
	const int cursor = g_select->cursor;

	tputs(tgetstr("cl", NULL), 0,output);
	ioctl(0, TIOCGWINSZ, &wn);
	g_select->win_col = wn.ws_col;
	g_select->rows_count = wn.ws_row;
	g_select->col = g_select->win_col / (g_select->max_len + 1);
	g_select->max_col = g_select->count / wn.ws_row + !!(g_select->count % wn.ws_row);
	if (g_select->col * g_select->rows_count >= g_select->count)
	{
		g_select->cursor = 0;
		print_args(g_select);
		g_select->cursor = cursor;
		cursor_move(g_select, 0);
	}
	else
		ft_putendl_fd("To Small", 0);
}
