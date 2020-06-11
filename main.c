/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 20:00:45 by sghezn            #+#    #+#             */
/*   Updated: 2020/06/11 08:45:36 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	ft_init_term(void)
{
	char	buf[BUFF_SIZE];
	int		res;

	if (!isatty(0))
		ft_error("ft_select: not a terminal");
	if ((res = tgetent(buf, g_select.term)) < 1)
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

void	ft_init_args(int argc, char **argv)
{
	int	i;

	i = 0;
	g_select.argc = argc - 1;
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
		c = 0;
		ft_display();
		read(0, &c, 8);
		if (c == ENTER_KEY)
			break ;
		else if (c == ESCAPE_KEY)
			ft_quit();
		else if (c == SPACE_KEY)
		{
			(*g_select.curr)->selected = !(*g_select.curr)->selected;
			g_select.selected += ((*g_select.curr)->selected) ? 1 : -1;
		}
		else if (c == DELETE_KEY || c == BCKSPC_KEY)
			ft_del_arg();
		else
			ft_move(c);
	}
}

int		main(int argc, char **argv, char **env)
{
	if (argc < 2)
		ft_error("usage: ft_select argument [argument [...]]");
	if (!*env || !(g_select.term = getenv("TERM")))
		ft_error("ft_select: TERM environment variable not set");
	ft_init_term();
	ft_init_args(argc, argv);
	ft_init_signal_handler();
	ft_select();
	tcsetattr(0, TCSANOW, &g_select.old_termios);
	tputs(tgetstr("cl", NULL), 1, ft_putc);
	tputs(tgetstr("ve", NULL), 1, ft_putc);
	ft_print_selection();
	ft_free_args();
	return (0);
}
