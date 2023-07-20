# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/31 18:14:12 by lhasmi            #+#    #+#              #
#    Updated: 2023/07/20 17:18:52 by lhasmi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

SRCS	= init.c routines.c philoutils.c philoutils_bis.c threads_bis.c main.c ft_strncmp.c \
			ft_isint.c ft_strlen.c ft_isnumber.c free_argv.c ft_split.c \
			ft_strlcpy.c ft_error.c	ft_wcount.c ft_atoi.c


OBJS	= $(SRCS:.c=.o)
CC		= gcc
FLAGS	= -g -pthread -Wall -Wextra -Werror -fsanitize=address

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(SRCS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean:
	rm -rf $(OBJS) $(NAME)

re: fclean all


.PHONY: all clean fclean re
