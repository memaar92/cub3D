# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/19 14:16:52 by mamesser          #+#    #+#              #
#    Updated: 2023/10/09 15:27:33 by mamesser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address

MLXFLAGS = -L/usr/X11/lib -lX11 -lXext -lm #-O3

SRCS_DIR = ./srcs/

SRCS := $(addprefix $(SRCS_DIR),raycaster.c \
								parser_utils1.c \
								parser_utils2.c \
								parser.c parser2.c \
								parser3.c \
								init.c \
								main.c \
								setup_view.c \
								init_raycasting.c \
								raycaster_utils.c \
								dda_utils.c \
								utils.c \
								key_hooks.c \
								mini_map.c \
								mini_map_utils.c \
								free_mem.c \
								mouse_move.c \
								floor_ceiling.c \
								hand_item.c \
								init_tex.c \
								alloc_tex.c)

LIBFT_DIR = ./libft

LIBFT = $(LIBFT_DIR)/libft.a

MLXLIB_DIR = ./minilibx

MLXLIB = $(MLXLIB_DIR)/libmlx.a

OBJS := $(SRCS:$(SRCS_DIR)%.c=$(SRCS_DIR)%.o)

HEADERS = cub.h

.PHONY: clean fclean re all

all: $(NAME)

$(NAME): $(OBJS) $(MLXLIB) $(LIBFT)
	cc $(CFLAGS) $(OBJS) $(MLXLIB) $(LIBFT) $(MLXFLAGS) -o $@

$(LIBFT):
	$(MAKE) bonus -C $(LIBFT_DIR)

$(MLXLIB):
	$(MAKE) -C $(MLXLIB_DIR)

$(SRCS_DIR)%.o: $(SRCS_DIR)%.c $(HEADERS)
	cc $(CFLAGS) -I. -c $< -o $@

install on linux:
	@sudo apt update && sudo apt install build-essential libx11-dev libglfw3-dev libglfw3 xorg-dev libbsd-dev

bonus: all

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLXLIB_DIR)
	rm -f $(OBJS)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all
