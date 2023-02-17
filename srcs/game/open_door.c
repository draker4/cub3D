/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:47:19 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/17 11:48:04 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	cube->map[y][x] = 3;
	change_obj_state(cube, (double)x + 0.5, (double)y + 0.5, 0);
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
	int	i;

	i = 1;
	while (cube->map[(int)(cube->player.pos_y + i * cube->player.dir_y)] \
	[(int)(cube->player.pos_x + i * cube->player.dir_x)] != 1)
	{
		if (cube->map[(int)(cube->player.pos_y + i * cube->player.dir_y)] \
		[(int)(cube->player.pos_x + i * cube->player.dir_x)] == 3)
			open_door(cube, (int)(cube->player.pos_y + i * \
			cube->player.dir_y), (int)(cube->player.pos_x + i * \
			cube->player.dir_x));
		else if \
		(cube->map[(int)(cube->player.pos_y + i * cube->player.dir_y)] \
		[(int)(cube->player.pos_x + i * cube->player.dir_x)] == 4)
			close_door(cube, (int)(cube->player.pos_y + i * \
			cube->player.dir_y), (int)(cube->player.pos_x + i * \
			cube->player.dir_x));
		i++;
	}
}

void	open_close_door(t_cube *cube)
{
	if (cube->weapon.gun)
		check_door_gun(cube);
	else
		check_door_punch(cube);
}
