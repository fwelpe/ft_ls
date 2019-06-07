# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thaley <thaley@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/05 17:28:26 by thaley            #+#    #+#              #
#    Updated: 2019/06/05 17:39:31 by thaley           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

CFLAGS = -g #-Wall -Wextra -Werror -g

SRC = $(wildcard *.c)

OBJ = $(SRC:.c=.o)

OBJLIB = ./libft/*.o

$(NAME): $(OBJ)
	make -C ./libft
	gcc $(CFLAGS) -o $(NAME) $(OBJ) -L libft/ -lft

all: $(NAME)

clean:
	make -C ./libft clean
	rm -f *.o

fclean:
	make -C ./libft fclean
	rm -f $(NAME)

re: fclean all