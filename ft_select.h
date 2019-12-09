/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 12:55:33 by yabakhar          #+#    #+#             */
/*   Updated: 2019/12/09 16:44:27 by aait-ihi         ###   ########.fr       */
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
#include <sys/ioctl.h>
#define BUTTON_UP 4283163
#define BUTTON_DOWN 4348699
#define BUTTON_RIGHT 4414235
#define BUTTON_LEFT 4479771
#define BUTTON_SPACE 32
#define BUTTON_ENTER 10
#define BUTTON_DEL 127
#define BUTTON_DEL2 2117294875
#define BUTTON_END 4610843
#define BUTTON_HOME 4741915
#define BUTTON_R 114

int fd;

typedef struct		s_item
{
	char			*content;
	_Bool			selected;
	int				len;
}					t_item;

typedef struct		s_ft_select
{
	t_item			*items;
	struct termios	config0;
	struct termios	config;
	int				fd;
	int				cursor;
	int				count;
	int				col;
	int				rows_count;
	int				win_col;
	int				max_col;
	int				max_len;
}					t_ft_select;

t_ft_select			*g_select;

void				cur_up(t_ft_select *ft_select);
void				cur_down(t_ft_select *ft_select);
void				cur_right(t_ft_select *ft_select);
void				cur_left(t_ft_select *ft_select);
void				cur_from_to(t_ft_select *ft_select, int from, int to);
void				reset(int ac, char **av, t_ft_select *ft_select);
void				select_item(t_ft_select *ft_select);
void				delete_item(t_ft_select *ft_select);
void				rediment(void);
void				end(t_ft_select *ft_select);

void				set_signal(void);

int		output(int str);
void	print_args(t_ft_select *ft_select);
void	set_items(int ac, char **av, t_ft_select *ft_select);
void	cursor_move(t_ft_select *ft_select, int old_cursor, int new_cursor);
void	cur_goto(t_ft_select *ft_select, int cursor);
void	configure_terminal(t_ft_select *ft_select);

void	deactive_modes();
void	active_modes(t_ft_select *ft_select,int  cursor);


void	delete_char(t_ft_select *ft_select, size_t num);
void	delete_last_line(t_ft_select *ft_select);
void	clean_win(t_ft_select *ft_select);

void sig_dispatch(int a);
