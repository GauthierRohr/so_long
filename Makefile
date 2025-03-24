NAME = so_long

CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I ./libft -I ./minilibx
# AUDIO
INCLUDES += -I/opt/homebrew/include/SDL2
# Options de lien
LDFLAGS = -L/opt/homebrew/lib -lSDL2 -lSDL2_mixer

# Répertoire des objets
OBJ_DIR = obj

# Sources
SRCS =	src/audio.c \
		src/check_rectangular_map.c \
		src/check_valid_path.c \
		src/check_wall_contour.c \
		src/enemies.c \
        src/input.c \
        src/load_textures.c \
		src/loop_hook.c \
		src/main.c \
        src/map.c \
        src/render.c

# Fichiers objets (avec le répertoire obj)
OBJS = $(SRCS:src/%.c=$(OBJ_DIR)/%.o)

# Libraries
LIBFT = ./libft/libft.a
MLX_MAC = ./minilibx/libmlx.a
MLX_LINUX = ./minilibx/libmlx_Linux.a

# OS Detection
UNAME := $(shell uname)

# Rules
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX_MAC) $(MLX_LINUX)
ifeq ($(UNAME), Darwin)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_MAC) -framework OpenGL -framework AppKit $(LDFLAGS) -o $(NAME)
else ifeq ($(UNAME), Linux)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_LINUX) -lXext -lX11 -lm $(LDFLAGS) -o $(NAME)
else
	@echo "Unsupported OS: $(UNAME)"
	@exit 1
endif

$(LIBFT):
	$(MAKE) -C ./libft

$(MLX_MAC):
ifeq ($(UNAME), Darwin)
	$(MAKE) -C ./minilibx
endif

$(MLX_LINUX):
ifeq ($(UNAME), Linux)
	$(MAKE) -C ./minilibx
endif

# Règle pour créer les fichiers objets dans le répertoire obj
$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(OBJ_DIR) # Créer le répertoire obj si nécessaire
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) # Supprimer le répertoire obj et son contenu
	$(MAKE) -C ./libft clean
	$(MAKE) -C ./minilibx clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re