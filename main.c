/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 00:57:15 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/12/07 07:00:15 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

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

void init(int ac, char **av, t_ft_select *ft_select)
{
	char buf[1024];
	struct termios config;
	int i;

	i = 0;
	ft_select->fd = open("/dev/tty", O_RDWR);
	if (ft_select->fd < 0 || !(ft_select->items = malloc(sizeof(t_item) * ac)))
		exit(-1);
	set_items(ac, av, ft_select);
	if (tcgetattr(0, &config) < 0)
		puts("error");
	config.c_lflag &= ~(ECHO | ICANON);
	if (tcsetattr(0, 0, &config) < 0)
		puts("error");
	tgetent(buf, getenv("TERM"));
	tputs(tgetstr("ti", 0), 0, output);
	tputs(tgetstr("vi", 0), 0, output);
	rediment();
	output(ft_select->fd + 255);
	
}

int main(int ac, char **av)
{
	t_ft_select ft_select;
	int button;

	g_select = &ft_select;
	ft_select.count = ac;
	ft_select.cursor = 0;
	ft_select.max_len = 0;
	init(ac, av, &ft_select);
	while (1)
	{
		button = 0;
		if (read(0, &button, sizeof(int)) > 0)
		{
			if (button == BUTTON_UP)
				cur_up(&ft_select);
			else if (button == BUTTON_DOWN)
				cur_down(&ft_select);
			else if (button == BUTTON_RIGHT)
				cur_right(&ft_select);
			else if (button == BUTTON_LEFT)
				cur_left(&ft_select);
			else if (button == BUTTON_SPACE)
				select_item(&ft_select);
			else if (button == BUTTON_ENTER)
				end(&ft_select);
			else if (button == BUTTON_DEL)
				delete_item(&ft_select);
		}
	}
}
