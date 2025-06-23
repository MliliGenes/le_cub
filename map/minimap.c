#include "../include/game.h"

void	render_minimap(t_game *game)
{
	reset_minimap(game);
	render_world_on_minimap(game);
	draw_player(game->img_minimap);
	draw_dir(game->img_minimap, game->player_data, (t_vec2i){MINIMAP_WIDTH / 2,
		MINIMAP_HEIGHT / 2});
}
