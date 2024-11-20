# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paranha <paranha@student.42sp.org.br>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/13 15:15:38 by paranha           #+#    #+#              #
#    Updated: 2024/05/16 13:30:33 by phraranha        ###   ########.org.br    #
#                                                                              #
# **************************************************************************** #

RED		=	\033[0;31m
GRN		=	\033[0;32m
YLW		=	\033[0;33m
BLU		=	\033[0;34m
MAG		=	\033[0;35m
CYA		=	\033[0;36m
WHT		=	\033[0;37m
RST		=	\033[0m

NAME	=	pipex

FILES	=	command.c \
		environment.c \
		split.c \
		string.c \
		close.c \
		main.c \

SRCDIR	=	src
SRC		=	$(FILES:%.c=$(SRCDIR)%.o)

OBJDIR	=	obj
OBJ		=	${FILES:%.c=$(OBJDIR)/%.o}

CC		=	cc
CFLGS	=	-Wextra -Wall -Werror

LIBFT	=	./libs/libft

INCLUDE	=	-I ./inc -I $(LIBFT)
LIBS	=	$(LIBFT)/libft.a

all: $(NAME)

$(NAME): $(LIBS) $(OBJ)
	rm -rf $(DEL)
	$(CC) $(CFLGS) $(OBJ) $(LIBS) $(INCLUDE) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLGS) $(INCLUDE) -c $< -o $@
	@echo "${GRN}Compile $@ DONE${RST}"

$(LIBS):
	@make -C $(LIBFT)

clean:
	@rm -rf $(OBJDIR)
	@echo "${RED}CLEAN:	Objects $(OBJ) DELETED${RST}"

fclean: clean
	@make fclean -sC $(LIBFT)
	@echo "${RED}CLEAN:	Lib $(LIBFT) DELETED${RST}"
	@rm -rf $(NAME)
	@echo "${RED}FCLEAN $(NAME) DELETED${RST}"

re: clean all

.PHONY: all, clean, fclean, re
