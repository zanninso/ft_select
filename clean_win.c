/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_win.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 01:18:50 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/12/09 01:48:11 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void delete_char(t_ft_select *ft_select, size_t num)
{
    char buffer[num];

    tputs(tgetstr("sc", 0), 0, output);
    ft_memset(buffer, ' ', num);
    write(ft_select->fd, buffer, num);
    tputs(tgetstr("rc", 0), 0, output);
}

void delete_last_line(t_ft_select *ft_select)
{
    int li;
    int co;
    char buffer[ft_select->max_len];

    ft_memset(buffer, ' ', ft_select->max_len);
    li = (ft_select->count - 1) % ft_select->rows_count;
    co = (ft_select->max_len + 1) * ((ft_select->count - 1) / ft_select->rows_count);
    tputs(tgoto(tgetstr("cm", 0), co, li), 0, output);
    write(ft_select->fd, buffer, ft_select->max_len);
}

void clean_win(t_ft_select *ft_select)
{
    int i;

    i = 0;
    while (i < ft_select->rows_count)
    {
        tputs(tgoto(tgetstr("cm", 0), 0, i), 0, output);
        delete_char(ft_select, ft_select->win_col);
        i++;
    }
}