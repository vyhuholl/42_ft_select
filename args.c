/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 05:35:15 by sghezn            #+#    #+#             */
/*   Updated: 2020/06/14 01:23:27 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	ft_new_arg(char *value)
{
	t_arg	*prev;
	t_arg	*arg;

	arg = (t_arg*)ft_memalloc(sizeof(t_arg));
	arg->value = ft_strdup(value);
	if (!g_select.args)
	{
		arg->prev = arg;
		arg->next = arg;
		g_select.args = arg;
		g_select.curr = &g_select.args;
	}
	else
	{
		prev = g_select.args->prev;
		arg->next = g_select.args;
		g_select.args->prev = arg;
		arg->prev = prev;
		prev->next = arg;
	}
}

int		ft_max_arg_len(void)
{
	t_arg	*start;
	t_arg	*ptr;
	int		curr;
	int		max;

	max = 0;
	if (!g_select.args || !g_select.args->value)
		return (max);
	start = g_select.args;
	ptr = start;
	while (ptr)
	{
		if ((curr = ft_strlen(ptr->value)) > max)
			max = curr;
		if (ptr->next == start)
			break ;
		ptr = ptr->next;
	}
	return (max);
}

void	ft_del_arg(void)
{
	t_arg	*curr;

	if (!g_select.curr)
		return ;
	curr = *g_select.curr;
	if (g_select.args == curr)
		g_select.args = (curr->next != curr) ? curr->next : NULL;
	else
		g_select.curr = &curr->next;
	curr->next->prev = curr->prev;
	curr->prev->next = curr->next;
	free(curr->value);
	curr->value = NULL;
	free(curr);
	curr = NULL;
	g_select.argc--;
	if (!g_select.argc)
		ft_quit();
}

void	ft_display_args(t_arg *args, t_arg *start, int rows, int cols)
{
	int	len;
	int	i;
	int	j;

	i = -1;
	while (++i < rows)
	{
		j = -1;
		while (++j < cols)
		{
			(args == (*g_select.curr)) ? ft_putstr_fd(UNDERLINE, 0) : 0;
			(args->selected) ? ft_putstr_fd(INV_VIDEO, 0) : 0;
			ft_putstr_fd(args->value, 0);
			ft_putstr_fd(RESET, 0);
			len = ft_strlen(args->value);
			while (len++ < ft_max_arg_len() && rows != 1)
				ft_putchar_fd(' ', 0);
			(j < cols - 1) ? ft_putchar_fd(' ', 0) : 0;
			if (args->next == start)
				break ;
			args = args->next;
		}
		(i < rows - 1) ? ft_putchar_fd('\n', 0) : 0;
	}
}

void	ft_free_args(void)
{
	t_arg	*start;
	t_arg	*curr;

	start = g_select.args;
	while (g_select.args)
	{
		curr = g_select.args;
		free(g_select.args->value);
		g_select.args->value = NULL;
		free(curr);
		curr = NULL;
		g_select.argc--;
		if (g_select.args->next == start)
			break ;
		g_select.args = g_select.args->next;
	}
	g_select.args = NULL;
}
