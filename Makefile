# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yun <marvin@42.fr>                         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/08 14:28:31 by yun               #+#    #+#              #
#    Updated: 2021/12/05 10:50:59 by yun              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = srcs/philosophers.c srcs/tools.c srcs/exit.c srcs/init.c srcs/actions.c srcs/death.c

HEADER = srcs/philosophers.h

OBJS = $(SRCS:%.c=%.o)

CPP = clang
CFLAGS = -Wall -Wextra -Werror -pthread

.cpp.o:
	$(CPP) $(CFLAGS) -c $< -o $(<:.cpp=.o) -I ./$(HEADER)

all: $(NAME)

$(NAME):	$(OBJS) $(HEADER)
	$(CPP) $(CFLAGS) -o $(NAME) $(SRCS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all re fclean clean
