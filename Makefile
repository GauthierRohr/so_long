# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+     #
#    By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        #
#                                                 +#+#+#+#+#+   +#+           #
#    Created: 2025/04/12 17:17:39 by grohr             #+#    #+#             #
#    Updated: 2025/04/12 20:01:04 by grohr            ###   ########.fr       #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CC = gcc
FLAGS = -Wall -Wextra -Werror -g
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11

# Répertoires
SRC_DIR = src/
OBJ_DIR = obj/

# Sources et objets
SRCS =	events.c \
		free.c \
		init_img.c \
		init.c \
		main.c \
		map_reader.c \
		map_validator.c \
		path_finder.c \
		player.c \
		render.c
SRC = $(addprefix $(SRC_DIR),$(SRCS))
OBJ = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

# Librairies
MLX_DIR 	= minilibx-linux
MLX 		= $(MLX_DIR)/libmlx_Linux.a
LIBFT_DIR 	= libft
LIBFT 		= $(LIBFT_DIR)/libft.a

# Includes
INCLUDES = -I$(MLX_DIR) -I$(LIBFT_DIR)

# Couleurs
RED     = \033[31m
GREEN   = \033[32m
YELLOW  = \033[0;33m
BLUE    = \033[34m
PURPLE  = \033[0;35m
CYAN    = \033[36m
RESET   = \033[0m

TOTAL := $(words $(OBJ))
COUNT = $(words $^)

# Barre de progression
define PROGRESS_BAR
	$(eval COMPILED += 1)
	$(eval PERCENT := $(shell echo $$(( $(COMPILED) * 100 / $(TOTAL) ))))
	@printf "\r$(CYAN)[so_long]$(RESET): Compilation... %-20s %3d%% " \
		$$(printf '$(GREEN)%0.s▮$(RESET)' $$(seq 1 $$(($(PERCENT) / 5)))) \
		$(PERCENT)
endef

# Règles
all: COMPILED=0
all: $(NAME)
	@echo "\n$(CYAN)[so_long]$(RESET):$(GREEN) Compilation terminée ! 🥳$(RESET)"

$(LIBFT):
	@if [ -f $(LIBFT_DIR)/Makefile ]; then \
		$(MAKE) -s -C $(LIBFT_DIR); \
	fi

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ)
	@if [ -f $(MLX_DIR)/Makefile ]; then \
		$(MAKE) -s -C $(MLX_DIR); \
	fi
	@$(CC) $(FLAGS) $(OBJ) -L$(LIBFT_DIR) -lft $(MLX_FLAGS) -o $(NAME)
	@echo "\n$(GREEN) Compilation de so_long réussie ! $(RESET)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) -c $< -o $@ $(INCLUDES)
	$(PROGRESS_BAR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@if [ -f $(MLX_DIR)/Makefile ]; then $(MAKE) -s -C $(MLX_DIR) clean; fi
	@if [ -f $(LIBFT_DIR)/Makefile ]; then $(MAKE) -s -C $(LIBFT_DIR) clean; fi
	@echo "$(CYAN)[so_long]$(RESET):$(GREEN) Fichiers objets => Cleaned!$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@if [ -f $(LIBFT_DIR)/Makefile ]; then $(MAKE) -s -C $(LIBFT_DIR) fclean; fi
	@echo "$(CYAN)[so_long]$(RESET):$(GREEN) Exécutable => Cleaned!$(RESET)"

re: fclean all

# Commandes fun
flex:
	@echo "🎉 Flexing those muscles! 📸"
	@sleep 0.5
	@echo "\n    ${RED}✨ ᕙ(⇀‸↼‶)ᕗ ✨${RESET}\n"
	@sleep 0.5
	@echo "\n    ${GREEN}   ᕙ(✧ڡ✧)ᕗ  ${RESET}\n"
	@sleep 0.5
	@echo "\n    ${YELLOW}⚡️ ᕙ(^▽^)ᕗ ⚡️${RESET}\n"
	@sleep 0.5
	@echo "\n    ${BLUE}   ᕦ(ò_óˇ)ᕤ  ${RESET}\n"
	@sleep 0.5
	@echo "\n    ${PURPLE}💥 ᕙ(▀̿̿Ĺ̯̿̿▀̿ ̿)ᕗ 💥${RESET}\n"
	@sleep 0.5
	@echo "\n🏆 Flex session complete! I'm a fcking boss!"

seum:
	@echo "\n ${RED}   ༼;´༎ຶ ۝ ༎ຶ༽ ${RESET}\n"
	@sleep 0.5
	@echo "\n ${GREEN}   (˚ ˃̣̣̥⌓˂̣̣̥ ) ${RESET}\n"
	@sleep 0.5
	@echo "\n ${CYAN}╭∩╮( •̀_•́ )╭∩╮${RESET}\n"
	@sleep 0.5
	@echo "\n ${PURPLE}   (ﾉಥ益ಥ) ${RESET}\n"
	@sleep 0.5
	@echo "\n ${YELLOW}   ᶠᶸᶜᵏᵧₒᵤ!${RESET}\n"
	@sleep 0.5

.PHONY: all clean fclean re flex seum
