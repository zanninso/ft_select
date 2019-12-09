/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 13:19:03 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/12/09 16:46:08 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void signal_stop()
{
	// if (tcsetattr(0, 0, &g_select->config0) == -1)
	// 	return ;
	// tputs(tgetstr("te", 0), 0, output);
	// tputs(tgetstr("ve", 0), 0, output);
	struct termios config;

	if (tcgetattr(0, &(config)) == -1)
		return ;
	config.c_lflag |= (ICANON | ECHO);
	signal(SIGTSTP, SIG_DFL);
	tcsetattr(0, 0,  &(config));
	tputs(tgetstr("te", NULL), 1, output);
	tputs(tgetstr("ve", NULL), 1, output);
	ioctl(0, TIOCSTI, (char[2]){config.c_cc[VSUSP],0});
}

void signal_cont()
{
	struct termios config;

	if (tcgetattr(0, &config) < 0)
		puts("error");
	config.c_lflag &= ~(ECHO | ICANON);
	if (tcsetattr(0, 0, &config) < 0)
		puts("error");
	tputs(tgetstr("ti", 0), 0, output);
	tputs(tgetstr("vi", 0), 0, output);
	signal(SIGTSTP, sig_dispatch);
	rediment();
}

void sig_dispatch(int a)
{
	if (a == SIGCONT)
		configure_terminal(g_select);
	else if (a == SIGTSTP)
		signal_stop();
	else if (a == SIGWINCH)
		rediment();
	else
		end(g_select);
}

void set_signal(void)
{
	int a;

	a = 1;
	while (a < 32)
	{
		signal(a, sig_dispatch);
		a++;
	}
}
