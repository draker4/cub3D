/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_sprites.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:23:56 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/15 19:31:07 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	can_move(double x, double y)
{
	if ((x - (int)x < 0.3 || (int) x + 1 - x < 0.3) || \
	(y - (int)y < 0.3 || (int) y + 1 - y < 0.3))
		return (1);
	return (0);
}

void	move_sprites_front(t_cube *cube)
{
	if (cube->move.up)
	{
		if (cube->map[(int)cube->player.pos_y][(int)(cube->player.pos_x + cube->\
		player.dir_x * cube->move.move_speed)] == 2 && can_move(cube->player.\
		pos_x + cube->player.dir_x * cube->move.move_speed, cube->player.pos_y))
			cube->player.pos_x += cube->player.dir_x * cube->move.move_speed;
		if (cube->map[(int)(cube->player.pos_y + cube->player.dir_y * cube->\
		move.move_speed)][(int)cube->player.pos_x] == 2 && can_move(cube->\
		player.pos_x, cube->player.pos_y + cube->player.dir_y * \
		cube->move.move_speed))
			cube->player.pos_y += cube->player.dir_y * cube->move.move_speed;
	}
	if (cube->move.down)
	{
		if (cube->map [(int)cube->player.pos_y][(int)(cube->player.pos_x
			- cube->player.dir_x * cube->move.move_speed)] == 2 &&
			can_move(cube->player.pos_x - cube->player.dir_x * \
			cube->move.move_speed, cube->player.pos_y))
			cube->player.pos_x -= cube->player.dir_x * cube->move.move_speed;
		if (cube->map[(int)(cube->player.pos_y - cube->player.dir_y
				* cube->move.move_speed)][(int)cube->player.pos_x] == 2 &&
				can_move(cube->player.pos_x, cube->player.pos_y - \
				cube->player.dir_y * cube->move.move_speed))
			cube->player.pos_y -= cube->player.dir_y * cube->move.move_speed;
	}
}

void	move_sprites_side(t_cube *cube)
{
	if (cube->move.left)
	{
		if (cube->map[(int)cube->player.pos_y][(int)(cube->player.pos_x + cube->\
		player.dir_y * cube->move.move_speed)] == 2 && can_move(cube->player.\
		pos_x + cube->player.dir_y * cube->move.move_speed, cube->player.pos_y))
			cube->player.pos_x += cube->player.dir_y * cube->move.move_speed;
		if (cube->map[(int)(cube->player.pos_y - cube->player.dir_x * cube->\
		move.move_speed)][(int)(cube->player.pos_x)] == 2 && can_move(cube->\
		player.pos_x, cube->player.pos_y - cube->player.dir_x * cube->\
		move.move_speed))
			cube->player.pos_y -= cube->player.dir_x * cube->move.move_speed;
	}
	if (cube->move.right)
	{
		if (cube->map[(int)cube->player.pos_y][(int)(cube->player.pos_x - cube->\
		player.dir_y * cube->move.move_speed)] == 2 && can_move(cube->\
		player.pos_x - cube->player.dir_y * cube->move.move_speed, \
		cube->player.pos_y))
			cube->player.pos_x -= cube->player.dir_y * cube->move.move_speed;
		if (cube->map[(int)(cube->player.pos_y + cube->player.dir_x * cube->\
		move.move_speed)][(int)(cube->player.pos_x)] == 2 && can_move(cube->\
		player.pos_x, cube->player.pos_y + cube->player.dir_x * cube->\
		move.move_speed))
			cube->player.pos_y += cube->player.dir_x * cube->move.move_speed;
	}
}
