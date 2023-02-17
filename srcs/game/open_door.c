/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:47:19 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/16 19:25:25 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	open_door(t_cube *cube)
{
	t_obj	*obj;

	cube->map[(int)(cube->player.pos_y + 1 * cube->player.dir_y)] \
	[(int)(cube->player.pos_x + 1 * cube->player.dir_x)] = 4;
	cube->boom.boom = 1;
	cube->boom.start_frame = 0;
	cube->boom.nb_frame = 0;
	// obj = new_obj() new xmp image
	// add sprite en posx posy
}

static void	close_door(t_cube *cube)
{
	cube->map[(int)(cube->player.pos_y + 1 * cube->player.dir_y)] \
	[(int)(cube->player.pos_x + 1 * cube->player.dir_x)] = 3;
	//delete sprite en pos y pos y
}

void	open_close_door(t_cube *cube)
{
	if (cube->map[(int)(cube->player.pos_y + cube->player.dir_y)] \
	[(int)(cube->player.pos_x + cube->player.dir_x)] != 1)
	{
		if (cube->map[(int)(cube->player.pos_y + 1 * cube->player.dir_y)] \
		[(int)(cube->player.pos_x + 1 * cube->player.dir_x)] == 3)
			open_door(cube);
		else if \
		(cube->map[(int)(cube->player.pos_y + 1 * cube->player.dir_y)] \
		[(int)(cube->player.pos_x + 1 * cube->player.dir_x)] == 4)
			close_door(cube);
	}
}
