/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:47:19 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/20 12:02:01 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	open_door(t_cube *cube, int y, int x)
{
	t_obj	*new;

	cube->map[y][x] = 4;
	new = new_obj((t_obj){(double)x + 0.5, (double)y + 0.5, 27, 0.0, 1, 1,
			0, 0, TIME_ANIM, 0, 0, 0, NULL}, cube, '4');
	if (!new)
		exit_game(cube, 1);
	obj_add_back(&cube->obj, new);
	cube->nb_objs = obj_size(cube->obj);
}

static void	close_door(t_cube *cube, int y, int x)
{
	t_obj	*obj;

	cube->map[y][x] = 3;
	obj = cube->obj;
	while (obj)
	{
		if (obj->pos_x == x + 0.5 && obj->pos_y == y + 0.5)
			break ;
		obj = obj->next;
	}
	if (!obj)
		return ;
	del_one(&cube->obj, obj);
	cube->nb_objs = obj_size(cube->obj);
}

static void	check_door_punch(t_cube *cube)
{
	if (cube->map[(int)(cube->player.pos_y + 1 * cube->player.dir_y)] \
	[(int)(cube->player.pos_x + 1 * cube->player.dir_x)] == 3)
		open_door(cube, (int)(cube->player.pos_y + 1 * \
		cube->player.dir_y), (int)(cube->player.pos_x + 1 * \
		cube->player.dir_x));
	else if \
	(cube->map[(int)(cube->player.pos_y + 1 * cube->player.dir_y)] \
	[(int)(cube->player.pos_x + 1 * cube->player.dir_x)] == 4)
		close_door(cube, (int)(cube->player.pos_y + 1 * \
		cube->player.dir_y), (int)(cube->player.pos_x + 1 * \
		cube->player.dir_x));
}

static void	check_door_gun(t_cube *cube)
{
	double	i;

	i = 0.5;
	while (cube->map[(int)(cube->player.pos_y + i * cube->player.dir_y)] \
	[(int)(cube->player.pos_x + i * cube->player.dir_x)] != 1)
	{
		if (cube->map[(int)(cube->player.pos_y + i * cube->player.dir_y)] \
		[(int)(cube->player.pos_x + i * cube->player.dir_x)] == 3)
		{
			open_door(cube, (int)(cube->player.pos_y + i * \
			cube->player.dir_y), (int)(cube->player.pos_x + i * \
			cube->player.dir_x));
			return ;
		}
		else if \
		(cube->map[(int)(cube->player.pos_y + i * cube->player.dir_y)] \
		[(int)(cube->player.pos_x + i * cube->player.dir_x)] == 4)
		{
			close_door(cube, (int)(cube->player.pos_y + i * \
			cube->player.dir_y), (int)(cube->player.pos_x + i * \
			cube->player.dir_x));
			return ;
		}
		i += 0.5;
	}
}

void	open_close_door(t_cube *cube)
{
	if (!cube->kill)
	{
		if (cube->weapon.gun)
			check_door_gun(cube);
		else
			check_door_punch(cube);
	}
	else
		cube->kill = 0;
}
