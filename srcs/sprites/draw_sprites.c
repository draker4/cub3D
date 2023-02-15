/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:15:51 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/15 13:49:07 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	calculate_distance(t_cube *cube)
{
	int	i;

	i = 0;
	while (i < NB_SPRITES)
	{
		cube->sprite[i].distance = \
		((cube->player.pos_x - cube->sprite[i].pos_x) * \
		(cube->player.pos_x - cube->sprite[i].pos_x)) + \
		((cube->player.pos_y - cube->sprite[i].pos_y) * \
		(cube->player.pos_y - cube->sprite[i].pos_y));
		i++;
	}
}

static void	sort_sprites(t_cube *cube)
{
	int			i;
	int			j;
	t_sprite	tmp;

	i = 0;
	while (i < NB_SPRITES)
	{
		j = i + 1;
		while (j < NB_SPRITES)
		{
			if (cube->sprite[j].distance > cube->sprite[i].distance)
			{
				tmp = cube->sprite[j];
				cube->sprite[j] = cube->sprite[i];
				cube->sprite[i] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	draw_sprites(t_cube *cube)
{
	int	i;

	cube->sprite[0] = (t_sprite){20.5, 11.5, 6, 0}; //green light in front of playerstart
	//green lights in every room
	cube->sprite[1] = (t_sprite){18.5, 4.5, 6, 0};
	cube->sprite[2] = (t_sprite){10.0, 4.5, 6, 0};
	cube->sprite[3] = (t_sprite){10.0, 12.5, 6, 0};
	cube->sprite[4] = (t_sprite){3.5, 6.5, 6, 0};
	cube->sprite[5] = (t_sprite){3.5, 20.5, 6, 0};
	cube->sprite[6] = (t_sprite){3.5, 14.5, 6, 0};
	cube->sprite[7] = (t_sprite){14.5, 20.5, 6, 0};

	//row of pillars in front of wall: fisheye test
	cube->sprite[8] = (t_sprite){18.5, 10.5, 8, 0};
	cube->sprite[9] = (t_sprite){18.5, 11.5, 8, 0};
	cube->sprite[10] = (t_sprite){18.5, 12.5, 8, 0};

	//some barrels around the map
	cube->sprite[11] = (t_sprite){21.5, 1.5, 7, 0};
	cube->sprite[12] = (t_sprite){15.5, 1.5, 7, 0};
	cube->sprite[13] = (t_sprite){16.0, 1.8, 7, 0};
	cube->sprite[14] = (t_sprite){16.2, 1.2, 7, 0};
	cube->sprite[15] = (t_sprite){3.5, 2.5, 7, 0};
	cube->sprite[16] = (t_sprite){9.5, 15.5, 7, 0};
	cube->sprite[17] = (t_sprite){10.0, 15.1, 7, 0};
	cube->sprite[18] = (t_sprite){10.5, 15.8, 7, 0};
	calculate_distance(cube);
	sort_sprites(cube);
	i = 0;
	while (i < NB_SPRITES)
	{
		init_calc_sprites(cube, i);
		calc_height_width(cube);
		draw_pixels_sprites(cube, i);
		i++;
	}
}
