/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:29:31 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/15 16:31:47 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	fill_background(t_cube *cube)
{
	int	x;
	int	y;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		y = 0;
		while (y < SCREEN_HEIGHT / 2)
		{
			cube->buffer[y][x] = cube->elem.floor_color;
			y++;
		}
		while (y < SCREEN_HEIGHT)
		{
			cube->buffer[y][x] = cube->elem.floor_color;
			y++;
		}
		x++;
	}
}

static int	update(t_cube *cube)
{
	cube->frame.time_prev = cube->frame.time_now;
	cube->frame.time_now = get_time();
	cube->frame.frame_time = cube->frame.time_now - cube->frame.time_prev;
	move_player(cube);
	if (cube->elem.floor_color != -1 || cube->elem.ceiling_color)
		raycast_floor_ceiling(cube);
	else
		fill_background(cube);
	raycast_walls(cube);
	draw_sprites(cube);
	draw_weapon(cube);
	draw_buffer(cube);
	mlx_put_image_to_window(cube->vars.mlx_ptr, cube->vars.mlx_win, \
	cube->data.img, 0, 0);
	return (EXIT_SUCCESS);
}

void	play_game(t_cube *cube)
{
	cube->frame.time_now = get_time();
	mlx_hook(cube->vars.mlx_win, 17, 0, &exit_game, cube);
	mlx_hook(cube->vars.mlx_win, 2, 1L << 0, &handle_keypress, cube);
	mlx_hook(cube->vars.mlx_win, 3, 1L << 1, &handle_keyrelease, cube);
	mlx_loop_hook(cube->vars.mlx_ptr, &update, cube);
	mlx_loop(cube->vars.mlx_ptr);
}
