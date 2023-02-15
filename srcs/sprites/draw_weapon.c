/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_weapon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:22:21 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/15 16:28:56 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	choose_anim(t_cube *cube)
{
	static double	time;

	if (!cube->attack)
		cube->weapon.nb_frame = 0;
	else
	{
		cube->weapon.start_frame += cube->frame.frame_time;
		if (cube->weapon.start_frame > time)
		{
			cube->weapon.nb_frame++;
			time += 0.2;
		}
	}
	if (cube->weapon.nb_frame == 3)
	{
		cube->weapon.nb_frame = 0;
		time = 0;
		cube->attack = 0;
	}
}

void	draw_weapon(t_cube *cube)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	choose_anim(cube);
	while (x < SCREEN_WIDTH)
	{
		y = 0;
		while (y < SCREEN_HEIGHT)
		{
			color = cube->weapon.tex[cube->weapon.nb_frame] \
			[SCREEN_HEIGHT * x + y];
			if ((color & 0x00FFFFFF) != 0)
				cube->buffer[y][x] \
				= color;
			y++;
		}
		x++;
	}
}
