NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror -O3 -fsanitize=address -g3
INCLUDES = -I./include

MLX_LIB = libmlx42.a
MLX_FLAGS = -lglfw -L/Users/sel-mlil/goinfre/homebrew/opt/glfw/lib -fsanitize=address

SRCDIR = .
EVENT_DIR = event_listner
INIT_DIR = init
LIB_DIR = lib
PLAYER_DIR = player
RAYCAST_DIR = raycaster

MAIN_SRC = main.c

EVENT_SRC = event_listner/event_listner.c \
           event_listner/game_loop.c

INIT_SRC = init/init_game.c \
          init/init_map.c \
          init/init_player.c \
          init/init_rays.c \
          init/init_walls.c

LIB_SRC = lib/deg_to_rad.c \
         lib/normalize_angle.c \
         lib/pixel.c

PLAYER_SRC = player/player.c

RAYCAST_SRC = raycaster/build_walls.c \
             raycaster/ray_caster.c \
             raycaster/rays_to_walls.c

SRC = $(MAIN_SRC) $(EVENT_SRC) $(INIT_SRC) $(LIB_SRC) $(PLAYER_SRC) $(RAYCAST_SRC)

OBJ = $(SRC:.c=.o)

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(CYAN)Linking $(NAME)...$(RESET)"
	@$(CC) $(OBJ)  $(MLX_FLAGS) $(MLX_LIB) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) created successfully!$(RESET)"

%.o: %.c
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -f $(OBJ)
	@echo "$(GREEN)✓ Object files cleaned!$(RESET)"

fclean: clean
	@echo "$(RED)Cleaning executable...$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)✓ Everything cleaned!$(RESET)"

re: fclean all

run: $(NAME)
	@echo "$(MAGENTA)Running $(NAME)...$(RESET)"
	@./$(NAME)

debug: CFLAGS += -g3 -fsanitize=address
debug: clean $(NAME)
	@echo "$(BLUE)✓ Debug build created!$(RESET)"

help:
	@echo "$(CYAN)Available targets:$(RESET)"
	@echo "  $(GREEN)all$(RESET)     - Build the program"
	@echo "  $(GREEN)clean$(RESET)   - Remove object files"
	@echo "  $(GREEN)fclean$(RESET)  - Remove object files and executable"
	@echo "  $(GREEN)re$(RESET)      - Rebuild everything"
	@echo "  $(GREEN)run$(RESET)     - Build and run the program"
	@echo "  $(GREEN)debug$(RESET)   - Build with debug flags"
	@echo "  $(GREEN)help$(RESET)    - Show this help message"

show:
	@echo "$(CYAN)Project structure:$(RESET)"
	@echo "$(YELLOW)Source files:$(RESET)"
	@for file in $(SRC); do echo "  - $$file"; done
	@echo "$(YELLOW)Object files:$(RESET)"
	@for file in $(OBJ); do echo "  - $$file"; done

.PHONY: all clean fclean re run debug help show