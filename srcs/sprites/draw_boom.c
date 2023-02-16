/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_boom.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:12:32 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/16 17:29:52 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	choose_anim(t_cube *cube)
{
	static double	time;

	cube->frame.start_boom += cube->frame.frame_time;
	if (cube->frame.start_boom > time)
	{
		cube->frame.nb_boom++;
		time += 0.1;
	}
	if (cube->frame.nb_boom == 20)
	{
		cube->frame.boom = 0;
		time = 0;
	}
}

void	draw_boom(t_cube *cube)
{
	int	x;
	int	y;
	int	color;

	x = SCREEN_WIDTH / 2 - TEX_WIDTH / 2;
	choose_anim(cube);
	if (cube->frame.nb_boom == 20)
		return ;
	while (x < TEX_WIDTH)
	{
		y = SCREEN_HEIGHT / 2 - TEX_HEIGHT / 2;
		while (y < TEX_HEIGHT)
		{
			color = cube->tex.texture[cube->frame.nb_boom] \
			[SCREEN_HEIGHT * x + y];
			if ((color & 0x00FFFFFF) != 0)
				cube->buffer[y][x] = color;
			y++;
		}
		x++;
	}
}
