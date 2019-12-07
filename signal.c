/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 13:19:03 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/12/07 13:25:07 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void			analyse(int a)
{
	// if (a == SIGCONT)
	// 	signal_cont();
	// else if (a == SIGTSTP)
	// 	signal_stop();
	/* else*/ if (a == SIGWINCH)
		rediment();
	// else
	// 	arret_forcer();
}

void			set_signal(void)
{
	int				a;

	a = 1;
	while (a < 32)
	{
		signal(a, analyse);
		a++;
	}
}
