/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_boom.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:12:32 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/17 17:13:33 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// static void	choose_anim(t_cube *cube)
// {
// 	static double	time;

// 	cube->boom.start_frame += cube->frame.frame_time;
// 	if (cube->boom.start_frame > time)
// 	{
// 		cube->boom.nb_frame++;
// 		time += 0.1;
// 	}
// 	if (cube->boom.nb_frame == 5)
// 	{
// 		cube->boom.boom = 0;
// 		time = 0.1;
// 	}
// }

// void	draw_boom(t_cube *cube)
// {
// 	int	x;
// 	int	y;
// 	int	color;

// 	x = 0;
// 	choose_anim(cube);
// 	while (x < 860)
// 	{
// 		y = 0;
// 		while (y < SCREEN_HEIGHT)
// 		{
// 			color = cube->boom.tex[cube->boom.nb_frame] 
// 			[SCREEN_HEIGHT * x + y];
// 			if ((color & 0x00FFFFFF) != 0)
// 				cube->buffer[y][x + 500] = color;
// 			y++;
// 		}
// 		x++;
// 	}
// }
