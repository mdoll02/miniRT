# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kschmidt <kschmidt@42wolfsburg.de>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/11 13:36:31 by kschmidt          #+#    #+#              #
#    Updated: 2022/12/13 17:34:46 by kschmidt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_memset.c \
	   ft_memcpy.c \
	   ft_memmove.c \
	   ft_memchr.c \
	   ft_memcmp.c \
	   ft_bzero.c \
	   ft_calloc.c \
	   ft_isalpha.c \
	   ft_isdigit.c \
	   ft_isalnum.c \
	   ft_isascii.c \
	   ft_isprint.c \
	   ft_strlen.c \
	   ft_strlcpy.c \
	   ft_strlcat.c \
	   ft_toupper.c \
	   ft_tolower.c \
	   ft_strchr.c \
	   ft_strrchr.c \
	   ft_strncmp.c \
	   ft_strnstr.c \
	   ft_atoi.c \
	   ft_strdup.c \
	   ft_substr.c \
	   ft_strjoin.c \
	   ft_strnjoin.c \
	   ft_strtrim.c \
	   ft_split.c \
	   ft_itoa.c \
	   ft_strmapi.c \
	   ft_striteri.c \
	   ft_putchar_fd.c \
	   ft_putstr_fd.c \
	   ft_putendl_fd.c \
	   ft_putnbr_fd.c \
	   ft_free_split.c \
	   ft_arraylen.c \
	   ft_strndup.c \
	   ft_strcmp.c \

SRCSB = ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \

NAME = libft.a

OBJS_DIR = objs
OBJS = $(SRCS:.c=.o)
OBJS := $(addprefix $(OBJS_DIR)/, $(OBJS))

OBJSB = $(SRCSB:.c=.o)
OBJSB := $(addprefix $(OBJS_DIR)/, $(OBJSB))


CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

$(OBJS_DIR)/%.o: %.c
	mkdir -p $(OBJS_DIR)
	echo "Compiling $< to $@"
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	ar rs $(NAME) $(OBJS)
	echo "Created $(NAME)"

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: $(OBJS) $(OBJSB)
	ar rs $(NAME) $(OBJS) $(OBJSB)
	echo "Created Bonus $(NAME)"

test: all
	$(CC) $(CFLAGS) main.c -L. -lft -o test
	./test

.PHONY: all clean fclean re

