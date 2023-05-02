NAME := miniRT

CC := gcc

CFLAGS := -Wall -Wextra -Werror -g
# CFLAGS := $(CFLAGS) -fsanitize=address

SRC := main.c \
		hooks/hooks.c \
		hooks/close.c \
		hooks/keys.c \

SRC_DIR := src
OBJ_DIR := obj

MLX_DIR := ext/minilibx-linux
LIBS := -L/usr/X11/lib -lm -lX11 -lXext

INCLUDES := -I includes -I $(MLX_DIR) -I /usr/X11/include

MLX := -L$(MLX_DIR)/mlx -lmlx

OBJ := $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(MLX_DIR)/mlx 2> /dev/null
	@make -C ext/libft
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MLX) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/hooks
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
	@echo "Compiling $<"


clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(MLX_DIR)/mlx clean
	@make -C ext/libft clean

fclean: clean
	@rm -f $(NAME)
	@make -C ext/libft fclean

re: fclean all

.PHONY: all clean fclean re