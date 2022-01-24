# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/24 13:38:51 by 0xNino            #+#    #+#              #
#    Updated: 2022/01/24 14:23:40 by 0xNino           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex
LIBFT	= libft

LIB_DIR	= ./libft
LIB		= ./libft/libft.a

GREEN	= \033[1;32m
RED 	= \033[1;31m
ORANGE	= \033[1;33m
RESET	= \033[0m

CC		= cc
CFLAGS	= -Wall -Werror -Wextra
RM		= rm -f

SRCS	= src/pipex.c

OBJS	= ${SRCS:.c=.o}

all: $(LIBFT) $(NAME)

$(NAME):	$(LIBFT) $(OBJS)
			@$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIB)
			@echo "[$(GREEN)pipex\tcompiled$(RESET)]"

$(LIBFT):
			@$(MAKE) -sC $(LIB_DIR)
			@echo "[$(GREEN)libft\tcompiled$(RESET)]"

clean:
		@$(MAKE) -sC $(LIB_DIR) clean
		@echo "[$(RED)libft\tdeleted$(RESET)]"
		@$(RM) $(OBJS)
		@echo "[$(RED)pipex\tdeleted$(RESET)]"

fclean:	clean
		@$(RM) $(NAME)
		@$(MAKE) -sC $(LIB_DIR) fclean

re:		fclean all

.PHONY:	all clean fclean re