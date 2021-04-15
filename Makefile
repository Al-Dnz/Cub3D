SRC =	main.c \
		draw_util.c \
		map_parser.c \
		map_array_generator.c \
		map_util.c \
		map_error.c \
		key_handler.c \
		game_process.c \
		move_handler.c \
		raycasting_init.c \
		raycasting_operation.c \
		graphic_engine.c \
		texture_handler.c \
		texture_util.c \
		sprite_handler.c \
		sprite_util.c \
		save_handler.c \
		hud_handler.c \
		exit_process.c \
		cub3d_util.c \
		main_initialisation.c \
		main_parser.c \
		set_parameters.c \
		set_map.c

NAME = Cub3D

MLX_DIR = mlx
MLX = libmlx.dylib
CC = gcc
LIB = ./libft/libft.a

CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address

OBJ_DIR = obj
SRC_DIR = src
INC_DIR = inc

OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
DPD = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.d))

.c.o:
	${CC} ${CFLAGS} -c$< -o ${<:.c=.o}
all:
	@(make -C ./libft/)
	@$(MAKE) -j $(NAME)
$(NAME): $(OBJ)
	${CC} $(CFLAGS) -o $(NAME) $(OBJ) $(LIB) -I $(INC_DIR) -L $(MLX_DIR) -l mlx
	@install_name_tool -change $(MLX) @loader_path/$(MLX_DIR)/$(MLX) $(NAME)
	@echo "\n------------------------------"
	@echo "| => $(NAME) well created ! <= |"
	@echo "------------------------------\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(MLX_DIR)/$(MLX) | .gitignore
		@mkdir -p $(OBJ_DIR)
		${CC} $(CFLAGS) -I $(INC_DIR) -I $(MLX_DIR) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@(make clean -C ./libft/)
	@echo "obj deleted"

fclean:	clean
	@rm -rf $(NAME)
	@(make fclean -C ./libft/)
	@echo "\n=> [$(NAME)]: deleted <=\n"

re: fclean all

.PHONY: all, clean, fclean, re

-include $(DPD)