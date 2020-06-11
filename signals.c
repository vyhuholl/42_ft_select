/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 20:48:22 by sghezn            #+#    #+#             */
/*   Updated: 2020/06/11 11:45:22 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	ft_error(char *str)
{
	ft_putendl_fd(str, 2);
	exit(EXIT_FAILURE);
}

int		ft_putc(int c)
{
	return (write(0, &c, 1));
}

void	ft_quit(void)
{
	tcsetattr(0, TCSANOW, &g_select.old_termios);
	tputs(tgetstr("ve", NULL), 1, ft_putc);
	ft_free_args();
	exit(EXIT_SUCCESS);
}

void	ft_stop(void)
{
	tcsetattr(0, TCSANOW, &g_select.old_termios);
	tputs(tgetstr("cl", NULL), 1, ft_putc);
	tputs(tgetstr("ve", NULL), 1, ft_putc);
	signal(SIGTSTP, SIG_DFL);
	ioctl(0, TIOCSTI, "\x1A");
}

void	ft_signal_handler(int signo)
{
	if (signo == SIGABRT || signo == SIGINT || signo == SIGKILL
			|| signo == SIGQUIT || signo == SIGSTOP)
		ft_quit();
	else if (signo == SIGTSTP)
		ft_stop();
	else if (signo == SIGCONT || signo == SIGWINCH)
	{
		if (signo == SIGCONT)
		{
			tcsetattr(0, TCSANOW, &g_select.new_termios);
			tputs(tgetstr("cl", NULL), 1, ft_putc);
			tputs(tgetstr("vi", NULL), 1, ft_putc);
			ft_init_signal_handler();
		}
		ft_display();
	}
}
