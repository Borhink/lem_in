# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/10 16:05:27 by qhonore           #+#    #+#              #
#    Updated: 2016/10/09 14:01:58 by qhonore          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./include/ ./libft/includes/
LIB_PATH = ./libft/

SRC_NAME = main.c utils.c parser.c finder.c move.c utils2.c
OBJ_NAME = $(SRC_NAME:.c=.o)
LIB_NAME = -lft
NAME = lem-in
DEP = include/lem_in.h

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))
LIB = $(addprefix -L,$(LIB_PATH))

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: lib
	@echo "\033[37;44m Make $(NAME) \033[0m"
	@make $(NAME)

$(NAME): $(OBJ)
	$(CC) $(LIB) $(LIB_NAME) $(FRAMEWORK) $^ -o $@

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(DEP) 
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

lib:
	@echo "\033[37;44m Make libft \033[0m"
	@make -C ./libft/

clean:
	rm -rf $(OBJ) $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)
	@make -C ./libft/ fclean

re: fclean all

.PHONY: lib clean fclean re
