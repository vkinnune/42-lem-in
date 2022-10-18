# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/11 15:06:38 by wdonnell          #+#    #+#              #
#    Updated: 2022/09/15 14:06:40 by wdonnell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= ant_cop
CC 		= gcc
CFLAGS	= -O3
SRCS	= ant_cop.c functions.c ft_strsplit.c
OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all
