NAME := miniRT

CC := gcc

CFLAGS := -Wall -Wextra -Werror -g
# CFLAGS := $(CFLAGS) -fsanitize=address

SRC := main.c \
		hooks/hooks.c \
		hooks/close.c \
		hooks/keys.c \
		parsing/rt_parser.c \
		parsing/parsing_utils.c \
		parsing/object_utils.c \
		parsing/ft_atof.c \
		parsing/error_handling_utils.c \
		parsing/set_utils.c \
		math/vector.c \
		math/vector_2.c \
		math/color.c \
		math/sphere_intersect.c \
		math/plane_intersect.c \
		math/cylinder_intersect.c \
		math/checkerboard_sample.c \
		math/vector_3.c \
		math/cylinder_helpers.c \
		rendering/render.c \
		rendering/lighting.c \
		rendering/calculate_rays.c \

SRC_DIR := src
OBJ_DIR := obj

MLX_DIR := ext/minilibx-linux
LIBS := -L/usr/X11/lib -lm -lX11 -lXext

INCLUDES := -I includes -I $(MLX_DIR) -I /usr/X11/include -I ext/libft

MLX := -L$(MLX_DIR)/mlx -lmlx

OBJ := $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(MLX_DIR)/mlx 2> /dev/null
	@make -C ext/libft
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MLX) $(LIBS) ext/libft/libft.a

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c includes/
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/hooks
	@mkdir -p $(OBJ_DIR)/parsing
	@mkdir -p $(OBJ_DIR)/rendering
	@mkdir -p $(OBJ_DIR)/math
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