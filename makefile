# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/24 17:44:40 by qbackaer          #+#    #+#              #
#    Updated: 2019/10/09 20:42:39 by qbackaer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -g
NAME = minishell
INCLUDES = minishell.h
SRCS = minishell.c display.c util.c execute.c getinput.c print.c setenv.c \
	   unsetenv.c cd.c expand.c echo.c
OBJS = minishell.o display.o util.o execute.o getinput.o print.o setenv.o \
	   unsetenv.o cd.o expand.o echo.c

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./libft
	$(CC) $(CFLAGS) $^ -I. ./libft/libft.a -o minishell
	rm -rf *.o

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -I. -c $^

clean:
	rm -rf *.o
	make fclean -C ./libft

fclean: clean
	rm -rf minishell

re: fclean all

.PHONY: re fclean clean all
