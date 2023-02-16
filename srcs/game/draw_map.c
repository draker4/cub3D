/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:29:31 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/16 17:12:38 by bboisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	define_map(t_cube *cube, int y, int x)
{
	double	map_x;
	double	map_y;

	map_x = cube->player.pos_x - 12.0 + ((x - MAP_POS) / 8);
	map_y = cube->player.pos_y - 12.0 + ((y - SCREEN_HEIGHT + MAP_SIZE
				+ MAP_POS) / 8);
	if (map_x < 0.0 || map_y < 0.0 || map_x > (double)cube->limits.x
		|| map_y > (double)cube->limits.y
		|| cube->map[(int)map_y][(int)map_x] == -1)
		cube->buffer[y][x] = BLACK;
	else if (cube->map[(int)map_y][(int)map_x] == 1)
		cube->buffer[y][x] = BLUE;
	else
		cube->buffer[y][x] = WHITE;
	if ((x > (MAP_SIZE / 2 + MAP_POS - 3) && x < (200 / 2 + MAP_POS + 3))
		&& (y > (SCREEN_HEIGHT - MAP_SIZE / 2 - MAP_POS - 3)
			&& y < (SCREEN_HEIGHT - MAP_SIZE / 2 - MAP_POS + 3)))
		cube->buffer[y][x] = RED;
}

void	draw_map(t_cube *cube)
{
	int	x;
	int	y;

	y = SCREEN_HEIGHT - MAP_SIZE - MAP_POS;
	while (y < SCREEN_HEIGHT - MAP_POS)
	{
		x = MAP_POS;
		while (x < MAP_SIZE + MAP_POS)
		{
			define_map(cube, y, x);
			x++;
		}
		y++;
	}
}
