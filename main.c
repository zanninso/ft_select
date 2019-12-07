/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 00:57:15 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/12/07 00:57:19 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void    set_items(int ac , char **av, t_item *items)
{
    int i;

    i = 0;
    while(i < ac)
    {
        items[i].content = av[i];
        items[i].selected = 0;
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
	set_items(ac, av, ft_select->items);
	if (tcgetattr(0, &config) < 0)
		puts("error");
	config.c_lflag &= ~(ECHO | ICANON);
	if (tcsetattr(0, 0, &config) < 0)
		puts("error");
	tgetent(buf, getenv("TERM"));
	tputs(tgetstr("ti", 0), 0, output);
	tputs(tgetstr("vi", 0), 0, output);
	print_args(ft_select);
	output(ft_select->fd + 255);
}

int main(int ac, char **av)
{
	t_ft_select ft_select;
	int button;
	
	ft_select.count = ac;
	ft_select.cursor = 0;
	init(ac, av, &ft_select);
	while (1)
	{
		button = 0;
		if (read(0, &button, sizeof(int)) > 0)
		{
			if (button == BUTTON_UP)
				up_cursor(&ft_select);
			else if (button == BUTTON_DOWN)
				down_cursor(&ft_select);
			else if (button == BUTTON_SPACE)
				select_item(&ft_select);
			else if (button == BUTTON_ENTER)
				end(&ft_select);
			else if (button == BUTTON_DEL)
				delete_item(&ft_select);
		}
	}
}
