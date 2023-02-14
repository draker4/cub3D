/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:29:31 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/14 18:00:28 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	update(t_cube *cube)
{
	cube->frame.time_prev = cube->frame.time_now;
	cube->frame.time_now = get_time();
	cube->frame.frame_time = cube->frame.time_now - cube->frame.time_prev;
	move_player(cube);
	raycast_floor_ceiling(cube);
	raycast_walls(cube);
	mlx_put_image_to_window(cube->vars.mlx_ptr, cube->vars.mlx_win, \
	cube->data.img, 0, 0);
	return (EXIT_SUCCESS);
}

void	play_game(t_cube *cube)
{
	cube->frame.time_now = get_time();
	mlx_hook(cube->vars.mlx_win, 2, 1L << 0, &handle_keypress, cube);
	mlx_hook(cube->vars.mlx_win, 3, 1L << 1, &handle_keyrelease, cube);
	mlx_hook(cube->vars.mlx_win, 17, 0, &exit_game, cube);
	mlx_loop_hook(cube->vars.mlx_ptr, &update, cube);
	mlx_loop(cube->vars.mlx_ptr);
}
