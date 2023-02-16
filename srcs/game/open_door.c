/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:47:19 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/16 16:12:11 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	open_close_door(t_cube *cube)
{
	if (cube->map[(int)(cube->player.pos_y + cube->player.dir_y)] \
	[(int)(cube->player.pos_x + cube->player.dir_x)] != 1)
	{
		if (cube->map[(int)(cube->player.pos_y + 1 * cube->player.dir_y)] \
		[(int)(cube->player.pos_x + 1 * cube->player.dir_x)] == 3)
			cube->map[(int)(cube->player.pos_y + 1 * cube->player.dir_y)] \
			[(int)(cube->player.pos_x + 1 * cube->player.dir_x)] = 4;
		else if \
		(cube->map[(int)(cube->player.pos_y + 1.5 * cube->player.dir_y)] \
		[(int)(cube->player.pos_x + 1.5 * cube->player.dir_x)] == 3)
			cube->map[(int)(cube->player.pos_y + 1.5 * cube->player.dir_y)] \
			[(int)(cube->player.pos_x + 1.5 * cube->player.dir_x)] = 4;
		else if \
		(cube->map[(int)(cube->player.pos_y + 1.5 * cube->player.dir_y)] \
		[(int)(cube->player.pos_x + 1.5 * cube->player.dir_x)] == 4)
			cube->map[(int)(cube->player.pos_y + 1.5 * cube->player.dir_y)] \
			[(int)(cube->player.pos_x + 1.5 * cube->player.dir_x)] = 3;
	}
}
