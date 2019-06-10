# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thaley <thaley@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/05 17:28:26 by thaley            #+#    #+#              #
#    Updated: 2019/06/10 14:13:29 by thaley           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
OBJ_DIR = objects/
CFLAGS = -g #-Wall -Wextra -Werror

SRC = $(wildcard *.c)

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

$(NAME): $(OBJ_DIR) $(OBJ)
	make -C ./libft
	gcc $(CFLAGS) -o $(NAME) $(OBJ) -L libft/ -lft

$(OBJ_DIR):
	mkdir $@

$(OBJ_DIR)%.o: %.c
	gcc $(FLAGS) -o $@ -c $^

all: $(NAME)

clean:
	make -C ./libft clean
	rm -f $(OBJ)

fclean: clean
	make -C ./libft fclean
	rm -f $(NAME)
	rm -rf $(OBJ_DIR)

re: fclean all