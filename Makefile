NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -O3
LDFLAGS =
INCLUDES = -I./include

MLX42_LIB_DIR = .

# MLX_LIBRARIES = -L"/Users/sahamzao/.brew/opt/glfw/lib/" -lglfw

MLX_LIBRARIES = -L"/Users/sel-mlil/goinfre/homebrew/opt/glfw/lib" -lglfw \
		libmlx42.a \
		-framework Cocoa -framework OpenGL -framework IOKit -lm -ldl

EVENT_DIR = event_listner
INIT_DIR = init
LIB_DIR = lib
PLAYER_DIR = player
RAYCAST_DIR = raycaster

INCLUDE_SRC = include/cub3d.h \
	    include/dependencies.h \
	    include/init.h \
	    include/lib.h \
	    include/parsing.h \
	    include/structs.h \
	    include/game.h \
	    include/MLX42.h

MAIN_SRC = main.c

EVENT_SRC = event_listner/event_listner.c \
	   event_listner/game_loop.c

INIT_SRC = init/init_game.c \
	  init/init_map.c \
	  init/init_player.c \
	  init/init_rays.c \
	  init/init_textures.c \
	  init/init_walls.c

LIB_SRC = lib/deg_to_rad.c \
	 lib/normalize_angle.c \
	 lib/pixel.c \
	 lib/ft_memset.c

PLAYER_SRC = player/player.c \
			player/mouse_handle.c

RAYCAST_SRC = raycaster/build_walls.c \
	     raycaster/ray_caster.c \
	     raycaster/rays_to_walls.c

PARSING_SRC = parsing/file_check.c \
	parsing/gnl.c \
	parsing/gnl_utils.c \
	parsing/parse_map.c \
	parsing/split.c \
	parsing/utils.c \
	parsing/parse_map_2.c \
	parsing/utils2.c \
	parsing/utils3.c  \
	parsing/parse_map_utils.c \
	parsing/parse_map_utils_2.c

MINIMAP_SRC = map/minimap_utils.c \
	map/minimap.c

SRC = $(MAIN_SRC) $(EVENT_SRC) $(INIT_SRC) $(LIB_SRC) $(PLAYER_SRC) $(RAYCAST_SRC) $(PARSING_SRC) $(MINIMAP_SRC)

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
	@$(CC) $(LDFLAGS) $(OBJ) $(MLX_LIBRARIES) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) created successfully!$(RESET)"

%.o: %.c $(INCLUDE_SRC)
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
	@./$(NAME) map.cub

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

push:
	git quick "lol"

.PHONY: all clean fclean re run debug help show