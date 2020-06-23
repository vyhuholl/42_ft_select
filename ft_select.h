/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 20:00:41 by sghezn            #+#    #+#             */
/*   Updated: 2020/06/23 06:52:26 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "libft/libft.h"
# include <curses.h>
# include <signal.h>
# include <stdlib.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>
# include <sys/ioctl.h>

# define WIDTH		0
# define HEIGHT		1

# define RESET		"\033[0m"
# define UNDERLINE	"\033[4m"
# define INV_VIDEO	"\033[7m"

# define ENTER_KEY	0xA
# define ESCAPE_KEY	0x1B
# define SPACE_KEY	0x20
# define BCKSPC_KEY	0x7F
# define UP_KEY		0x415B1B
# define DOWN_KEY	0x425B1B
# define RIGHT_KEY	0x435B1B
# define LEFT_KEY	0x445B1B
# define DELETE_KEY	0x7E335B1B

typedef struct		s_arg
{
	char			*value;
	int				selected;
	struct s_arg	*prev;
	struct s_arg	*next;
}					t_arg;

typedef struct		s_select
{
	int				argc;
	int				selected;
	t_arg			*curr;
	t_arg			*args;
	struct termios	old_termios;
	struct termios	new_termios;
}					t_select;

t_select			g_select;

void				ft_error(char *str);
int					ft_putc(int c);
void				ft_quit(void);
void				ft_stop(void);
void				ft_signal_handler(int signo);
void				ft_new_arg(char *value);
int					ft_max_arg_len(void);
void				ft_del_arg(t_arg **arg);
void				ft_display_args(t_arg *args, t_arg *start,
					int rows, int cols);
void				ft_free_args(void);
int					ft_window_size(int c);
int					ft_cols(void);
void				ft_move(long c);
void				ft_display(void);
void				ft_print_selection(void);
void				ft_init_term(void);
void				ft_init_args(char **argv);
void				ft_init_signal_handler(void);
void				ft_select(void);

#endif
