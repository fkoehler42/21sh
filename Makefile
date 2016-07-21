# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/26 11:46:03 by fkoehler          #+#    #+#              #
#    Updated: 2016/07/21 19:56:44 by fkoehler         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

vpath %.c ./src

SRC = buffer.c \
	  cmd_check_input.c \
	  cmd_parsing.c \
	  cmd_pipe.c \
	  cmd_storage.c \
	  cursor.c \
	  environ.c \
	  error.c \
	  free.c \
	  hist_storage.c \
	  history.c \
	  init.c \
	  input_cut_copy.c \
	  input_delete.c \
	  input_handling.c \
	  keys_parsing.c \
	  line_moves_1.c \
	  line_moves_2.c \
	  lst_tools.c \
	  main.c \
	  print.c \
	  prompt.c \
	  str_tools.c \
	  strsplit_args.c

NAME = 21sh

FLAGS = -Wall -Werror -Wextra -g -fsanitize=address

LIBDIR = ./libft/

INCLUDES = $(LIBDIR)includes/

LIB = $(LIBDIR)libft.a

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
		@gcc $(FLAGS) $(OBJ) -L$(LIBDIR) -lft -ltermcap -o $@
		@echo "\033[0;32m21sh compilation done !\033[0;m"

$(LIB):
	@make -C $(LIBDIR)

%.o: %.c
	@gcc $(FLAGS) -c $< -I . -I $(INCLUDES)

clean:
	@rm -f $(OBJ)
	@echo "\033[0;32mObject files deleted !\033[0;m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[0;32mExecutable deleted !\033[0;m"

re: fclean all
