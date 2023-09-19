# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/19 14:16:52 by mamesser          #+#    #+#              #
#    Updated: 2023/09/19 14:17:51 by mamesser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub

CFLAGS = -Wall -Wextra -Werror

MLXFLAGS = -L/usr/X11/lib -lX11 -lXext -lm

SRCS_DIR = ./srcs/

SRCS := $(addprefix $(SRCS_DIR),raycaster.c)

LIBFT_DIR = ./libft

LIBFT = $(LIBFT_DIR)/libft.a

MLXLIB_DIR = ./minilibx

MLXLIB = $(MLXLIB_DIR)/libmlx.a

OBJS := $(SRCS:$(SRCS_DIR)%.c=$(SRCS_DIR)%.o)

HEADERS = cub.h

.PHONY: clean fclean re all

all: $(NAME)

$(NAME): $(OBJS) $(MLXLIB) $(LIBFT)
	cc $(MLXFLAGS) $(MLXLIB) $(LIBFT) $(OBJS) -o $@

$(LIBFT):
	$(MAKE) bonus -C $(LIBFT_DIR)

$(MLXLIB):
	$(MAKE) -C $(MLXLIB_DIR)

$(SRCS_DIR)%.o: $(SRCS_DIR)%.c $(HEADERS)
	cc $(CFLAGS) -I. -c $< -o $@

bonus: all

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -f $(OBJS) 

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all