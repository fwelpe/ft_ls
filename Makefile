# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/05 17:28:26 by thaley            #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2019/06/10 17:09:01 by thaley           ###   ########.fr        #
=======
#    Updated: 2019/06/10 15:54:45 by cdenys-a         ###   ########.fr        #
>>>>>>> 1c000e2a58353b20dea962c0b27dd3d8b26148e8
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
	gcc $(CFLAGS) -o $@ -c $^

all: $(NAME)

clean:
	make -C ./libft clean
	rm -f $(OBJ)

fclean: clean
	make -C ./libft fclean
	rm -f $(NAME)
	rm -rf $(OBJ_DIR)

re: fclean all