# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lhasmi <lhasmi@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/31 18:14:12 by lhasmi            #+#    #+#              #
#    Updated: 2023/07/16 20:39:34 by lhasmi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

SRCS	= threads.c philoutils.c

OBJS	= $(SRCS:.c=.o)
CC		= gcc
FLAGS	= -g -pthread -Wall -Wextra -Werror -fsanitize=address

all: $(NAME)

$(NAME):
	$(CC) $(FLAGS) $(SRCS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean:
	rm -rf $(OBJS) $(NAME)

re: fclean all
