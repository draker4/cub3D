/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:47:19 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/17 10:31:53 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	change_obj_state(t_cube *cube, double x, double y, int state)
{
	t_obj	*obj;

	obj = cube->obj;
	while (obj)
	{
		if (obj->pos_x == x && obj->pos_y == y)
			break ;
		obj = obj->next;
	}
	if (!obj)
		return ;
	obj->draw = state;
	obj->start_frame = 0;
}

static void	open_door(t_cube *cube, int y, int x)
{
	cube->map[y][x] = 4;
	cube->boom.boom = 1;
	cube->boom.start_frame = 0;
	cube->boom.nb_frame = 0;
	change_obj_state(cube, (double)x + 0.5, (double)y + 0.5, 1);
}

static void	close_door(t_cube *cube, int y, int x)
{
	cube->map[(int)(cube->player.pos_y + 1 * cube->player.dir_y)] \
	[(int)(cube->player.pos_x + 1 * cube->player.dir_x)] = 3;
	change_obj_state(cube, (double)x + 0.5, (double)y + 0.5, 0);
}

void	open_close_door(t_cube *cube)
{
	if (cube->map[(int)(cube->player.pos_y + cube->player.dir_y)] \
	[(int)(cube->player.pos_x + cube->player.dir_x)] != 1)
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
}
