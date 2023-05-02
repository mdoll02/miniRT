NAME := miniRT

CC := gcc

CFLAGS := -Wall -Wextra -Werror -g
# CFLAGS := $(CFLAGS) -fsanitize=address

SRC := main.c \

SRC_DIR := src
OBJ_DIR := obj

ifeq ($(shell uname), Linux)
	MLX_DIR := ext/minilibx-linux
	LIBS := -lm -lX11 -lXext
else
	MLX_DIR := ext/minilibx-macos
	LIBS := -lm -framework OpenGL -framework AppKit
endif

INCLUDES := -I includes -I $(MLX_DIR)

MLX := -L$(MLX_DIR)/mlx -lmlx

OBJ := $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(MLX_DIR)/mlx
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MLX) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
	@echo "Compiling $<"


clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re