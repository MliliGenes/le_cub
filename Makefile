
# ! -L"/Users/sahamzao/.brew/opt/glfw/lib/" -lglfw
# * -L"/Users/sel-mlil/goinfre/homebrew/opt/glfw/lib" -lglfw

MLX_LIBRARIES = -L"/Users/sel-mlil/goinfre/homebrew/opt/glfw/lib" -lglfw \
		../mlx/libmlx42.a \
		-framework Cocoa -framework OpenGL -framework IOKit -lm -ldl


NAME = cub3d
BONUS = cub3d_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror -O3
LDFLAGS =
INCLUDES = -Imandatory/include
BONUS_INCLUDES = -Ibonus/include

# MLX_LIBRARIES = ../mlx/libmlx42_linux.a -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -lm -ldl

EVENT_DIR = event_listner
INIT_DIR = init
LIB_DIR = lib
PLAYER_DIR = player
RAYCAST_DIR = raycaster

MANDATORY_INCLUDE_SRC = mandatory/include/cub3d.h \
	    mandatory/include/dependencies.h \
	    mandatory/include/init.h \
	    mandatory/include/lib.h \
	    mandatory/include/parsing.h \
	    mandatory/include/structs.h \
	    mandatory/include/game.h \
	    ../mlx/MLX42.h

MAIN_SRC = main.c \
		cleanup.c

EVENT_SRC = event_listner/event_listner.c \
	   event_listner/game_loop.c

INIT_SRC = init/init_game.c \
	  init/init_player.c \
	  init/init_rays.c \
	  init/init_textures.c \
	  init/init_textures_utils.c \
	  init/init_walls.c

LIB_SRC = lib/deg_to_rad.c \
	 lib/normalize_angle.c \
	 lib/pixel.c \
	 lib/ft_memset.c

PLAYER_SRC = player/player.c \
			player/open_door.c \
			player/mouse_handle.c

RAYCAST_SRC = raycaster/build_walls.c \
	     raycaster/ray_caster.c \
	     raycaster/dda_utils.c \
	     raycaster/floor_cell.c \
	     raycaster/rays_to_walls.c

PARSING_SRC = parsing/file_check.c \
	parsing/checkinox.c\
	parsing/check_2.c\
	parsing/gnl.c \
	parsing/gnl_utils.c \
	parsing/parse_map.c \
	parsing/split.c \
	parsing/utils.c \
	parsing/parse_map_2.c \
	parsing/parse_map_utils_3.c \
	parsing/utils2.c \
	parsing/utils3.c  \
	parsing/utils4.c \
	parsing/utils5.c \
	parsing/parse_map_utils.c \
	parsing/ft_freeing_free.c\
	parsing/parse_map_utils_2.c

MINIMAP_SRC = map/minimap_utils.c \
	map/minimap.c

SRC = $(MAIN_SRC) $(EVENT_SRC) $(INIT_SRC) $(LIB_SRC) $(PLAYER_SRC) $(RAYCAST_SRC) $(PARSING_SRC) $(MINIMAP_SRC)

SRC_MANDATORY = $(addprefix mandatory/, $(SRC))

OBJ_MANDATORY = $(SRC_MANDATORY:.c=.o)

SRC_BONUS = $(addprefix bonus/, $(SRC))

OBJ_BONUS = $(SRC_BONUS :.c=.o)

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
RESET = \033[0m

all: $(NAME)

bonus: $(BONUS)

$(NAME): $(OBJ_MANDATORY)
	@echo "$(CYAN)Linking $(NAME)...$(RESET)"
	@$(CC) $(LDFLAGS) $(OBJ_MANDATORY) $(MLX_LIBRARIES) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) created successfully!$(RESET)"

$(BONUS): $(OBJ_BONUS)
	@echo "$(CYAN)Linking $(NAME)...$(RESET)"
	@$(CC) $(LDFLAGS) $(OBJ_BONUS) $(MLX_LIBRARIES) -o $(BONUS)
	@echo "$(GREEN)✓ $(OBJ_BONUS) created successfully!$(RESET)"

mandatory/%.o: mandatory/%.c $(MANDATORY_INCLUDE_SRC)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -f $(OBJ_MANDATORY)
	@echo "$(GREEN)✓ Object files cleaned!$(RESET)"

fclean: clean
	@echo "$(RED)Cleaning executable...$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)✓ Everything cleaned!$(RESET)"

re: fclean all

run: $(NAME)
	@echo "$(MAGENTA)Running $(NAME)...$(RESET)"
	@./$(NAME) levels/map.cub

debug: LDFLAGS += -g3 -fsanitize=address
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