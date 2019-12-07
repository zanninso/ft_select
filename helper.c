/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:44:38 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/12/07 13:43:56 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

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
	int line;
	int col;
	i = ft_select->cursor;
	while (i < ft_select->count)
	{
		if (ft_select->items[i].selected)
			tputs(tgetstr("mr", 0), 0, output);
		if(i == ft_select->cursor)
			tputs(tgetstr("us", 0), 0, output);
		line  = i % ft_select->rows_count;
		col = (ft_select->max_len + 1) * (i / ft_select->rows_count);
		tputs(tgoto(tgetstr("cm", 0), col, line), 0, output);
		ft_putstr_fd(ft_select->items[i].content, ft_select->fd);
		tputs(tgetstr("me", 0), 0, output);
		i++;
	}
}
