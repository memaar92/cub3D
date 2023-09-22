# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: valmpani <valmpanis@student.42wolfsburg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/15 11:52:07 by mamesser          #+#    #+#              #
#    Updated: 2023/09/21 16:50:01 by valmpani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CFLAGS = -Wall -Wextra -Werror

SRCS = \
		ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
		ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
		ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
		ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
		ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_isspace.c \

BONUS_SRCS = \
		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
		ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
		ft_lstmap.c

GNL_DIR = ./gnl/

GNL_SRCS := $(addprefix $(GNL_DIR),get_next_line_bonus.c get_next_line_utils_bonus.c)

GNL_OBJS := $(GNL_SRCS:$(GNL_DIR)%.c=$(GNL_DIR)%.o)

BONUS_OBJS := $(BONUS_SRCS:%.c=%.o)

OBJS := $(SRCS:%.c=%.o)

HEADERS = libft.h ./gnl/get_next_line_bonus.h

.PHONY: clean fclean re all bonus

all: $(NAME)

$(NAME): $(OBJS) $(GNL_OBJS)
	@ar rcs $@ $^

bonus: $(BONUS_OBJS) $(OBJS) $(GNL_OBJS)
	@ar rcs $(NAME) $^

%.o: %.c $(HEADERS)
	@cc $(CFLAGS) -I . -c $< -o $@

$(GNL_DIR)%.o: $(GNL_DIR)%.c $(HEADERS)
	@cc $(CFLAGS) -I . -c $< -o $@

clean:
	@rm -f $(OBJS) $(BONUS_OBJS) $(GNL_OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all
