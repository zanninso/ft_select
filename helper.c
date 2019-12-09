/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:44:38 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/12/09 16:25:55 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void active_modes(t_ft_select *ft_select, int cursor)
{
	if (ft_select->items[cursor].selected)
		tputs(tgetstr("mr", 0), 0, output);
	if (ft_select->cursor == cursor)
		tputs(tgetstr("us", 0), 0, output);
}

void deactive_modes()
{
	tputs(tgetstr("me", 0), 0, output);
}

void cur_goto(t_ft_select *ft_select, int cursor)
{
	int co;
	int li;

	li = cursor % ft_select->rows_count;
	co = (ft_select->max_len + 1) * (cursor / ft_select->rows_count);
	//ft_select->cursor = cursor;
	tputs(tgoto(tgetstr("cm", 0), co, li), 0, output);
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

void set_items(int ac, char **av, t_ft_select *ft_select)
{
	int i;

	i = 0;
	while (i < ac)
	{
		ft_select->items[i].content = av[i];
		ft_select->items[i].selected = 0;
		ft_select->items[i].len = ft_strlen(av[i]);
		if (ft_select->max_len < ft_select->items[i].len)
			ft_select->max_len = ft_select->items[i].len;
		i++;
	}
}

void print_args(t_ft_select *ft_select)
{
	int i;

	i = ft_select->cursor;
	while (i < ft_select->count)
	{
		cur_goto(ft_select, i);
		delete_char(ft_select, ft_select->max_len);
		active_modes(ft_select, i);
		ft_putstr_fd(ft_select->items[i].content, ft_select->fd);
		deactive_modes();
		i++;
	}
}

void configure_terminal(t_ft_select *ft_select)
{
	char buf[1024];

	if (tcgetattr(0, &ft_select->config0) < 0)
		puts("error");
	ft_memcpy(&ft_select->config, &ft_select->config, sizeof(struct termios));
	ft_select->config.c_lflag &= ~(ECHO | ICANON);
	if (tcsetattr(0, 0, &ft_select->config) < 0)
		puts("error");
	tgetent(buf, getenv("TERM"));
	tputs(tgetstr("ti", 0), 0, output);
	tputs(tgetstr("vi", 0), 0, output);
}
