/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 12:53:00 by sghezn            #+#    #+#             */
/*   Updated: 2020/06/11 08:57:36 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		ft_window_size(int c)
{
	struct winsize ws;

	ioctl(0, TIOCGWINSZ, &ws);
	return ((c == WIDTH) ? ws.ws_col : ws.ws_row);
}

int		ft_cols(void)
{
	int	cols;

	cols = ft_window_size(WIDTH) / (ft_max_arg_len() + 1);
	(!cols) ? cols = 1 : 0;
	if ((ft_max_arg_len() + 1) * g_select.argc < ft_window_size(WIDTH))
		cols = g_select.argc;
	return (cols);
}

void	ft_move(long c)
{
	t_arg	*curr;
	int		cols;
	int		i;

	i = 0;
	cols = ft_cols();
	curr = *g_select.curr;
	if (c == UP_KEY || c == LEFT_KEY)
	{
		while (c == UP_KEY && ++i < cols)
			curr = curr->prev;
		g_select.curr = &curr->prev;
	}
	else if (c == DOWN_KEY || c == RIGHT_KEY)
	{
		while (c == DOWN_KEY && ++i < cols)
			curr = curr->next;
		g_select.curr = &curr->next;
	}
}

void	ft_display(void)
{
	int	rows;
	int	cols;

	if (!g_select.argc || ft_max_arg_len() > ft_window_size(WIDTH))
		return ;
	tputs(tgetstr("cl", NULL), 1, ft_putc);
	cols = ft_cols();
	rows = g_select.argc / cols;
	if (rows > ft_window_size(HEIGHT))
		return ;
	rows += (g_select.argc % cols) ? 1 : 0;
	ft_display_args(g_select.args, g_select.args, rows, cols);
}

void	ft_print_selection(void)
{
	t_arg	*start;
	t_arg	*ptr;
	int		c;

	c = 0;
	if (!g_select.args || !g_select.selected)
		return ;
	start = g_select.args;
	ptr = start;
	while (ptr)
	{
		if (ptr->selected)
		{
			ft_putstr(ptr->value);
			(++c < g_select.selected) ? ft_putchar(' ') : ft_putchar('\n');
		}
		if (ptr->next == start)
			break ;
		ptr = ptr->next;
	}
}
