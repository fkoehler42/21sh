# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/26 11:46:03 by fkoehler          #+#    #+#              #
#    Updated: 2016/06/30 17:10:29 by fkoehler         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

vpath %.c ./src

SRC = cursor.c \
	  environ.c \
	  error.c \
	  init.c \
	  input.c \
	  line_moves_1.c \
	  line_moves_2.c \
	  main.c \
	  parse_keys.c \
	  print.c \
	  prompt.c

NAME = 21sh

FLAGS = -Wall -Werror -Wextra -g

LIBDIR = ./libft/

INCLUDES = $(LIBDIR)includes/

LIB = $(LIBDIR)libft.a

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
		@gcc $(FLAGS) $(OBJ) -L$(LIBDIR) -lft -ltermcap -o $@
		@echo "\033[0;32m21sh compilation done !"

$(LIB):
	@make -C $(LIBDIR)

%.o: %.c
	@gcc $(FLAGS) -c $< -I . -I $(INCLUDES)

clean:
	@rm -f $(OBJ)
	@echo "\033[0;32mObject files deleted !"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[0;32mExecutable deleted !"

re: fclean all
