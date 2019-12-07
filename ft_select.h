/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 12:55:33 by yabakhar          #+#    #+#             */
/*   Updated: 2019/12/07 00:20:50 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <curses.h>
#include <term.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "libft/libft.h"
#define BUTTON_UP 4283163
#define BUTTON_DOWN 4348699
#define BUTTON_SPACE 32
#define BUTTON_ENTER 10
#define BUTTON_DEL 127

int fd;

typedef struct		s_item
{
	char			*content;
	_Bool			selected;
}					t_item;

typedef struct		s_ft_select
{
	t_item			*items;
	int				fd;
	int				cursor;
	int				count;
}					t_ft_select;

void	up_cursor(t_ft_select *ft_select);
void	down_cursor(t_ft_select *ft_select);
void	select_item(t_ft_select *ft_select);
void	delete_item(t_ft_select *ft_select);
void	end(t_ft_select *ft_select);

int		output(int str);
void	print_args(t_ft_select *ft_select);
void	cursor_move(t_ft_select *ft_select, int old_cursor_position);