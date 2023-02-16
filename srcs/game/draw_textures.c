/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 18:18:44 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/16 16:32:20 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	find_index_texture(t_cube *cube)
{
	if (cube->raycast.door)
		cube->tex.tex_num = 9;
	else if (cube->raycast.side)
	{
		if (cube->raycast.ray_dir_y <= 0)
			cube->tex.tex_num = 0;
		else
			cube->tex.tex_num = 1;
	}
	else
	{
		if (cube->raycast.ray_dir_x <= 0)
			cube->tex.tex_num = 3;
		else
			cube->tex.tex_num = 2;
	}
}

void	calculate_texture(t_cube *cube)
{
	find_index_texture(cube);
	if (!cube->raycast.side)
		cube->tex.wall_hit_x = cube->player.pos_y + \
		cube->raycast.dist_plan_wall * cube->raycast.ray_dir_y;
	else
		cube->tex.wall_hit_x = cube->player.pos_x + \
		cube->raycast.dist_plan_wall * cube->raycast.ray_dir_x;
	cube->tex.wall_hit_x -= floor(cube->tex.wall_hit_x);
	cube->tex.tex_x = (int)(cube->tex.wall_hit_x * (double)(TEX_WIDTH));
	if (!cube->raycast.side && cube->raycast.ray_dir_x > 0)
		cube->tex.tex_x = TEX_WIDTH - cube->tex.tex_x - 1;
	if (cube->raycast.side == 1 && cube->raycast.ray_dir_y < 0)
		cube->tex.tex_x = TEX_WIDTH - cube->tex.tex_x - 1;
}

void	fill_texture(t_cube *cube, int x)
{
	int	y;

	cube->tex.step = 1.0 * TEX_HEIGHT / cube->raycast.line_height;
	cube->tex.tex_pos = (cube->raycast.line_start - SCREEN_HEIGHT / 2 + \
	cube->raycast.line_height / 2) * cube->tex.step;
	y = cube->raycast.line_start;
	while (y < cube->raycast.line_end)
	{
		cube->tex.tex_y = (int)cube->tex.tex_pos & (TEX_HEIGHT - 1);
		cube->tex.tex_pos += cube->tex.step;
		cube->tex.color = cube->tex.texture[cube->tex.tex_num][TEX_HEIGHT * \
		cube->tex.tex_x + cube->tex.tex_y];
		cube->buffer[y][x] = cube->tex.color;
		y++;
	}
}

void	draw_buffer(t_cube *cube)
{
	int	y;
	int	x;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			my_mlx_pixel_put(&cube->data, x, y, cube->buffer[y][x]);
			cube->buffer[y][x] = 0;
			x++;
		}
		y++;
	}
}
