/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 20:00:45 by sghezn            #+#    #+#             */
/*   Updated: 2020/06/23 07:33:38 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	ft_init_term(void)
{
	if (!getenv("TERM") || !ft_strlen(getenv("TERM")))
		ft_error("ft_select: TERM environment variable not set");
	if (!isatty(0))
		ft_error("ft_select: not a terminal");
	if (tgetent(NULL, getenv("TERM")) < 1)
		ft_error("ft_select: tgetent error");
	tcgetattr(0, &g_select.old_termios);
	tcgetattr(0, &g_select.new_termios);
	g_select.new_termios.c_lflag &= ~(ICANON | ECHO);
	g_select.new_termios.c_cc[VMIN] = 1;
	g_select.new_termios.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &g_select.new_termios);
	tputs(tgetstr("cl", NULL), 1, ft_putc);
	tputs(tgetstr("vi", NULL), 1, ft_putc);
}

void	ft_init_args(char **argv)
{
	int	i;

	i = 0;
	g_select.argc = 0;
	g_select.selected = 0;
	while (argv[++i])
		ft_new_arg(argv[i]);
}

void	ft_init_signal_handler(void)
{
	signal(SIGABRT, ft_signal_handler);
	signal(SIGCONT, ft_signal_handler);
	signal(SIGINT, ft_signal_handler);
	signal(SIGKILL, ft_signal_handler);
	signal(SIGQUIT, ft_signal_handler);
	signal(SIGSTOP, ft_signal_handler);
	signal(SIGTSTP, ft_signal_handler);
	signal(SIGWINCH, ft_signal_handler);
}

void	ft_select(void)
{
	long	c;

	while (42)
	{
		ft_display();
		c = 0;
		read(0, &c, 8);
		if (c == ENTER_KEY)
			break ;
		else if (c == ESCAPE_KEY)
			ft_quit();
		else if (c == SPACE_KEY)
		{
			g_select.curr->selected = !(g_select.curr->selected);
			g_select.selected += (g_select.curr->selected) ? 1 : -1;
			if (g_select.curr->selected)
				g_select.curr = g_select.curr->next;
		}
		else if (c == DELETE_KEY || c == BCKSPC_KEY)
			ft_del_arg(&g_select.curr);
		else
			ft_move(c);
	}
}

int		main(int argc, char **argv, char **env)
{
	if (argc < 2)
		ft_error("usage: ft_select argument [argument [...]]");
	if (!env || !*env)
		ft_error("ft_select: empty environment");
	ft_init_term();
	ft_init_args(argv);
	ft_init_signal_handler();
	ft_select();
	tcsetattr(0, TCSANOW, &g_select.old_termios);
	tputs(tgetstr("cl", NULL), 1, ft_putc);
	tputs(tgetstr("ve", NULL), 1, ft_putc);
	ft_print_selection();
	ft_free_args();
	return (0);
}
