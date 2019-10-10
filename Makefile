# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/24 17:44:40 by qbackaer          #+#    #+#              #
#    Updated: 2019/10/10 19:17:03 by qbackaer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = minishell
INCLUDES = minishell.h
SRCS = minishell.c display.c getinput.c expand.c execute.c setenv.c unsetenv.c \
       cd.c echo.c util.c util_tab.c util_pwd.c util_sys.c
OBJS = minishell.o display.o getinput.o expand.o execute.o setenv.o unsetenv.o \
       cd.o echo.o util.o util_tab.c util_pwd.o util_sys.o

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
