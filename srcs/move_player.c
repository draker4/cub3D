/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:42:44 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/08 19:57:52 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_player(t_cube *cube)
{
	cube->move->move_speed = cude->frame.frame_time * MOVE_SPEED;
	cube->move->rotate_speed = cude->frame.frame_time * ROT_SPEED;
	if (cube->move.up)
	{
		if (cube->map \
		[(int)(cube->player.pos_x + cube->player.dir_x * \
		cube->move->move_speed)][cube->player.pos_y] == 0)
			cube->player.pos_x += cube->player.dir_x * cube->move->move_speed;
	}
	if (cube->move.down)
	{
		if (cube->map \
		[(int)(cube->player.pos_x - cube->player.dir_x * \
		cube->move->move_speed)][cube->player.pos_y] == 0)
			cube->player.pos_x -= cube->player.dir_x * cube->move->move_speed;
	}
	if (cube->move.right)
	{
		game->player.prev_dir_x = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos();
	}
}
