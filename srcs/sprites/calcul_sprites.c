/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:34:00 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/15 14:23:34 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_calc_sprites(t_cube *cube, int i)
{
	cube->sprites.sprite_x = cube->sprite[i].pos_x - cube->player.pos_x;
	cube->sprites.sprite_y = cube->sprite[i].pos_y - cube->player.pos_y;
	cube->sprites.inv_mat = 1.0 / (cube->player.plane_x * cube->player.dir_y - \
	cube->player.dir_x * cube->player.plane_y);
	cube->sprites.transf_x = cube->sprites.inv_mat * (cube->player.dir_y * \
	cube->sprites.sprite_x - cube->player.dir_x * cube->sprites.sprite_y);
	cube->sprites.transf_y = cube->sprites.inv_mat * (-cube->player.plane_y * \
	cube->sprites.sprite_x + cube->player.plane_x * cube->sprites.sprite_y);
	cube->sprites.sp_screen_x = (int)((SCREEN_WIDTH / 2) * (1 + \
	cube->sprites.transf_x / cube->sprites.transf_y));
}

void	calc_height_width(t_cube *cube, int i)
{
	cube->sprites.move_screen = (int)(cube->sprite[i].v_move / \
	cube->sprites.transf_y);
	cube->sprites.sp_height = fabs(SCREEN_HEIGHT / cube->sprites.transf_y) / \
	cube->sprite[i].v_div;
	cube->sprites.start_y = -(int)(cube->sprites.sp_height) / 2 + \
	SCREEN_HEIGHT / 2 + cube->sprites.move_screen;
	if (cube->sprites.start_y < 0)
		cube->sprites.start_y = 0;
	cube->sprites.end_y = (int)(cube->sprites.sp_height) / 2 + \
	SCREEN_HEIGHT / 2 + cube->sprites.move_screen;
	if (cube->sprites.end_y >= SCREEN_HEIGHT)
		cube->sprites.end_y = SCREEN_HEIGHT - 1;
	cube->sprites.sp_width = fabs(SCREEN_HEIGHT / \
	cube->sprites.transf_y) / cube->sprite[i].u_div;
	cube->sprites.start_x = -(int)(cube->sprites.sp_width) / 2 + \
	cube->sprites.sp_screen_x;
	if (cube->sprites.start_x < 0)
		cube->sprites.start_x = 0;
	cube->sprites.end_x = (int)(cube->sprites.sp_width) / 2 + \
	cube->sprites.sp_screen_x;
	if (cube->sprites.end_x >= SCREEN_WIDTH)
		cube->sprites.end_x = SCREEN_WIDTH - 1;
}

void	draw_pixels_sprites(t_cube *cube, int i)
{
	int	x;
	int	y;

	x = cube->sprites.start_x - 1;
	while (++x < cube->sprites.end_x)
	{
		cube->sprites.tex_x = (int)(256 * (x - (-cube->sprites.sp_width / 2 + \
		cube->sprites.sp_screen_x)) * TEX_WIDTH / cube->sprites.sp_width) / 256;
		if (cube->sprites.transf_y > 0 && x > 0 && x < SCREEN_WIDTH && \
		cube->sprites.transf_y < cube->buffer_z[x])
		{
			y = cube->sprites.start_y - 1;
			while (++y < cube->sprites.end_y)
			{
				cube->sprites.d = (y - cube->sprites.move_screen) * 256 - \
				SCREEN_HEIGHT * 128 + cube->sprites.sp_height * 128;
				cube->sprites.tex_y = ((cube->sprites.d * TEX_HEIGHT) / \
				cube->sprites.sp_height) / 256;
				cube->sprites.color = cube->tex.texture [cube->sprite[i].\
				texture][TEX_WIDTH * cube->sprites.tex_x + cube->sprites.tex_y];
				if ((cube->sprites.color & 0x00FFFFFF) != 0)
					cube->buffer[y][x] = cube->sprites.color;
			}
		}
	}
}
