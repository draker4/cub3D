/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:29:31 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/15 20:49:32 by bboisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	define_map(t_cube *cube, int y, int x)
{
	double	map_x;
	double	map_y;

	map_x = cube->player.pos_x - 10.0 + ((x - 10) / 10);
	map_y = cube->player.pos_y - 10.0 + ((y - SCREEN_HEIGHT + 200 + 10) / 10);
	if (map_x < 0.0 || map_y < 0.0 || map_x > (double)cube->limits.x
		|| map_y > (double)cube->limits.y)
		cube->buffer[y][x] = 0xFFFFFF;
	else if (cube->map[(int)map_y][(int)map_x] == 1)
		cube->buffer[y][x] = 0x000000;
	else
		cube->buffer[y][x] = 0xFF0000;
	if ((x > (200 / 2 + 10) && x < (200 / 2 + 10 + 10)) && (y > (SCREEN_HEIGHT - 200 / 2 -10)
		&& y < (SCREEN_HEIGHT - 200 / 2 -10 + 10)))
		cube->buffer[y][x] = 0xFFFF00;
}

void	draw_map(t_cube *cube)
{
	int	x;
	int	y;

	y = SCREEN_HEIGHT - 200 - 10;
	while (y < SCREEN_HEIGHT - 10)
	{
		x = 10;
		while (x < 200 + 10)
		{
			define_map(cube, y, x);
			x++;
		}
		y++;
	}
}
