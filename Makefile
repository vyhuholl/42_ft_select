# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/08 17:00:35 by sghezn            #+#    #+#              #
#    Updated: 2020/06/10 04:06:56 by sghezn           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_select
INC = -I libft/libft.h -I ft_select.h
FLAG = -Wall -Wextra -Werror
TERM_FLAG = -ltermcap

SRC = 	args.c \
		display.c \
		main.c \
		signals.c \

OBJ = $(SRC:%.c=%.o)
D_FILE = $(SRC:%.c=%.d)

LIB_DIR = libft/
LIB = libft/libft.a

LIB_ALL = $(addsuffix .all,$(LIB_DIR))
LIB_CLEAN = $(addsuffix .clean,$(LIB_DIR))
LIB_FCLEAN = $(addsuffix .fclean,$(LIB_DIR))

all:	$(LIB_ALL) $(OBJ) $(NAME)

clean:	$(LIB_CLEAN)
	rm -rf $(OBJ) $(D_FILE)

fclean:	$(LIB_FCLEAN) clean
	rm -rf $(NAME)

re:	fclean all

%.o:	%.c
	gcc $(FLAG) -O2 -c $< -o $@ $(INC) -MD

$(NAME):	$(OBJ) $(LIB)
	gcc $(FLAG) $(OBJ) -o $(basename $(NAME)) $(LIB) $(TERM_FLAG)

%.all:
	make -C $*

%.clean:
	make -C $* clean

%.fclean:
	rm -f $(addsuffix *.a,$*)

include $(wildcard $(D_FILE))

.PHONY:	all clean fclean re
