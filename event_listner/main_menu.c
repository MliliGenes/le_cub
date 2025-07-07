// #include "../include/game.h"

// void animate(t_game *game, mlx_image_t *imgs[2])
// {
//     static int counter = 0;
//     static int frame = 0;
    
//     counter++;
    
//     // Change frame every 30000 iterations (adjust this value for speed)
//     if (counter >= 30000)
//     {
//         // Switch to next frame
//         frame = (frame + 1) % 2;
        
//         // Display the current frame
//         mlx_image_to_window(game->mlx, imgs[frame], 0, 0);
        
//         counter = 0; // Reset counter
//     }
// }

// void main_menu(t_game *game)
// {
//     mlx_texture_t *frames[2];
//     mlx_image_t *imgs[2];

    
//     frames[0] = mlx_load_png("imgs/frame_1.png");
//     frames[1] = mlx_load_png("imgs/frame_2.png");
//     imgs[0] = mlx_texture_to_image(game->mlx, frames[0]);
//     imgs[1] = mlx_texture_to_image(game->mlx, frames[1]);
    
//     // Show initial frame
//     mlx_image_to_window(game->mlx, imgs[0], 0, 0);
    
//     while (!game->start_game)
//     {
//         animate(game, imgs);
//     }
    
//     // Clean up
//     mlx_delete_image(game->mlx, imgs[0]);
//     mlx_delete_image(game->mlx, imgs[1]);
//     mlx_delete_texture(frames[0]);
//     mlx_delete_texture(frames[1]);
// }