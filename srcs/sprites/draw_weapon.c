/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_weapon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:22:21 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/17 11:27:57 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	choose_anim(t_cube *cube, int begin, int end)
{
	static double	time;

	if (!cube->attack)
		cube->weapon.nb_frame = begin;
	else
	{
		if (cube->weapon.start_frame > time)
		{
			cube->weapon.nb_frame++;
			time += 0.1;
		}
		if (cube->weapon.nb_frame == end + 1)
		{
			open_close_door(cube);
			cube->weapon.nb_frame = begin;
			time = 0;
			cube->attack = 0;
		}
		cube->weapon.start_frame += cube->frame.frame_time;
	}
}

void	draw_weapon(t_cube *cube)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	if (cube->weapon.gun)
		choose_anim(cube, 3, 6);
	else
		choose_anim(cube, 0, 2);
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
