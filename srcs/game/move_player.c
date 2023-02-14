/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:42:44 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/14 14:52:01 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	move_forward_backward(t_cube *cube)
{
	if (cube->move.up)
	{
		if (cube->map[(int)cube->player.pos_y][(int)(cube->player.pos_x
			+ cube->player.dir_x * cube->move.move_speed)] == 0)
			cube->player.pos_x += cube->player.dir_x * cube->move.move_speed;
		if (cube->map[(int)(cube->player.pos_y + cube->player.dir_y
				* cube->move.move_speed)][(int)cube->player.pos_x] == 0)
			cube->player.pos_y += cube->player.dir_y * cube->move.move_speed;
	}
	if (cube->move.down)
	{
		if (cube->map [(int)cube->player.pos_y][(int)(cube->player.pos_x
			- cube->player.dir_x * cube->move.move_speed)] == 0)
			cube->player.pos_x -= cube->player.dir_x * cube->move.move_speed;
		if (cube->map[(int)(cube->player.pos_y - cube->player.dir_y
				* cube->move.move_speed)][(int)cube->player.pos_x] == 0)
			cube->player.pos_y -= cube->player.dir_y * cube->move.move_speed;
	}
}

static void	move_right_left(t_cube *cube)
{
	if (cube->move.right)
	{
		if (cube->map[(int)cube->player.pos_y][(int)(cube->player.pos_x
			+ cube->player.dir_y * cube->move.move_speed)] == 0)
			cube->player.pos_x += cube->player.dir_y * cube->move.move_speed;
		if (cube->map[(int)(cube->player.pos_y - cube->player.dir_x
				* cube->move.move_speed)][(int)(cube->player.pos_x)] == 0)
			cube->player.pos_y -= cube->player.dir_x * cube->move.move_speed;
	}
	if (cube->move.left)
	{
		if (cube->map[(int)cube->player.pos_y][(int)(cube->player.pos_x
			- cube->player.dir_y * cube->move.move_speed)] == 0)
			cube->player.pos_x -= cube->player.dir_y * cube->move.move_speed;
		if (cube->map[(int)(cube->player.pos_y + cube->player.dir_x
				* cube->move.move_speed)][(int)(cube->player.pos_x)] == 0)
			cube->player.pos_y += cube->player.dir_x * cube->move.move_speed;
	}
}

static void	rotate_player(t_cube *cube, double prev_dir_x, double prev_plane_x)
{
	if (cube->move.rotate_right)
	{
		cube->player.dir_x = cube->player.dir_x * cos(-cube->move.rotate_speed) \
		- cube->player.dir_y * sin(-cube->move.rotate_speed);
		cube->player.dir_y = prev_dir_x * sin(-cube->move.rotate_speed) \
		+ cube->player.dir_y * cos(-cube->move.rotate_speed);
		cube->player.plane_x = cube->player.plane_x * \
		cos(-cube->move.rotate_speed) - cube->player.plane_y * \
		sin(-cube->move.rotate_speed);
		cube->player.plane_y = prev_plane_x * sin(-cube->move.rotate_speed) \
		+ cube->player.plane_y * cos(-cube->move.rotate_speed);
	}
	if (cube->move.rotate_left)
	{
		cube->player.dir_x = cube->player.dir_x * cos(cube->move.rotate_speed) \
		- cube->player.dir_y * sin(cube->move.rotate_speed);
		cube->player.dir_y = prev_dir_x * sin(cube->move.rotate_speed) \
		+ cube->player.dir_y * cos(cube->move.rotate_speed);
		cube->player.plane_x = cube->player.plane_x * \
		cos(cube->move.rotate_speed) - cube->player.plane_y * \
		sin(cube->move.rotate_speed);
		cube->player.plane_y = prev_plane_x * sin(cube->move.rotate_speed) \
		+ cube->player.plane_y * cos(cube->move.rotate_speed);
	}
}

void	move_player(t_cube *cube)
{
	double	prev_dir_x;
	double	prev_plane_x;

	prev_dir_x = cube->player.dir_x;
	prev_plane_x = cube->player.plane_x;
	cube->move.move_speed = cube->frame.frame_time * MOVE_SPEED;
	cube->move.rotate_speed = cube->frame.frame_time * ROT_SPEED;
	if (cube->move.up || cube->move.down)
		move_forward_backward(cube);
	if (cube->move.right || cube->move.left)
		move_right_left(cube);
	if (cube->move.rotate_left || cube->move.rotate_right)
		rotate_player(cube, prev_dir_x, prev_plane_x);
}
