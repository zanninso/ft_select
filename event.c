/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:44:12 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/12/09 15:41:15 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void select_item(t_ft_select *ft_select)
{
	ft_select->items[ft_select->cursor].selected ^= 1;
	active_modes(ft_select, ft_select->cursor);
	cur_goto(ft_select, ft_select->cursor);
	ft_putstr_fd(ft_select->items[ft_select->cursor].content, ft_select->fd);
	deactive_modes();
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
	delete_last_line(ft_select);
	delete_char(ft_select, ft_select->max_col);
	ft_select->count--;
	if (cursor < ft_select->count)
		ft_memcpy(&items[cursor], &items[cursor + 1], sizeof(t_item) * (count - cursor));
	else
		ft_select->cursor--;
	print_args(ft_select);
}

void end(t_ft_select *ft_select)
{
	int i;
	struct termios config;

	i = 0;
	if (tcgetattr(0, &(config)) == -1)
		return ;
	config.c_lflag |= (ICANON | ECHO);
	if (tcsetattr(0, 0, &(config)) == -1)
		return ;
	tputs(tgetstr("te", 0), 0, output);
	tputs(tgetstr("ve", 0), 0, output);
	while (i < ft_select->count)
	{
		if (ft_select->items[i].selected)
			ft_putendl_fd(ft_select->items[i].content, 0);
		i++;
	}

	exit(0);
}

void rediment(void)
{
	struct winsize wn;
	const int cursor = g_select->cursor;

	ioctl(0, TIOCGWINSZ, &wn);
	g_select->win_col = wn.ws_col;
	g_select->rows_count = wn.ws_row;
	clean_win(g_select);
	g_select->col = g_select->win_col / (g_select->max_len + 1);
	g_select->max_col = g_select->count / wn.ws_row + !!(g_select->count % wn.ws_row);
	if (g_select->col * g_select->rows_count >= g_select->count)
	{
		g_select->cursor = 0;
		print_args(g_select);
		g_select->cursor = cursor;
		cursor_move(g_select, g_select->cursor, 0);
	}
	else
		ft_putendl_fd("To Small", 0);
}

void reset(int ac, char **av, t_ft_select *ft_select)
{
	ft_select->count = ac;
	set_items(ac, av, ft_select);
	rediment();
	cursor_move(ft_select, ft_select->cursor, 0);
}
