/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_floor_ceiling.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:56:08 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/14 17:52:28 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_camera(t_cube *cube, int y)
{
	cube->bkground.ray_dir_x0 = cube->player.dir_x - cube->player.plane_x;
	cube->bkground.ray_dir_y0 = cube->player.dir_y - cube->player.plane_y;
	cube->bkground.ray_dir_x1 = cube->player.dir_x + cube->player.plane_x;
	cube->bkground.ray_dir_y1 = cube->player.dir_y + cube->player.plane_y;
	cube->bkground.center_y = y - SCREEN_HEIGHT / 2;
	cube->bkground.pos_z = 0.5 * SCREEN_HEIGHT;
	cube->bkground.hori_dist = cube->bkground.pos_z / cube->bkground.center_y;
}

static void	init_dir(t_cube *cube)
{
	cube->bkground.step_x = cube->bkground.hori_dist * \
	(cube->bkground.ray_dir_x1 - cube->bkground.ray_dir_x0) / SCREEN_WIDTH;
	cube->bkground.step_y = cube->bkground.hori_dist * \
	(cube->bkground.ray_dir_y1 - cube->bkground.ray_dir_y0) / SCREEN_WIDTH;
	cube->bkground.floor_x = cube->player.pos_x + cube->bkground.hori_dist * \
	cube->bkground.ray_dir_x0;
	cube->bkground.floor_y = cube->player.pos_y + cube->bkground.hori_dist * \
	cube->bkground.ray_dir_y0;
}

static void	draw_pixel(t_cube *cube, int x, int y)
{
	cube->bkground.tex_floor = 4;
	cube->bkground.tex_ceil = 5;
	cube->bkground.floor_color = cube->tex.texture[cube->bkground.tex_floor] \
	[TEX_WIDTH * cube->bkground.tex_y + cube->bkground.tex_x];
	//on garde que si utile de faire plus sombre
	cube->bkground.floor_color = (cube->bkground.floor_color >> 1) & 8355711;
	cube->buffer[y][x] = cube->bkground.floor_color;
	cube->bkground.ceil_color = cube->tex.texture[cube->bkground.tex_ceil] \
	[TEX_WIDTH * cube->bkground.tex_y + cube->bkground.tex_x];
	//on garde que si utile de faire plus sombre
	cube->bkground.ceil_color = (cube->bkground.ceil_color >> 1) & 8355711;
	cube->buffer[SCREEN_HEIGHT - y - 1][x] = cube->bkground.ceil_color;
}

static void	find_texture(t_cube *cube, int y)
{
	int	x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		cube->bkground.cell_x = (int)cube->bkground.floor_x;
		cube->bkground.cell_y = (int)cube->bkground.floor_y;
		cube->bkground.tex_x = (int)(TEX_WIDTH * (cube->bkground.floor_x - \
		cube->bkground.cell_x)) & (TEX_WIDTH - 1);
		cube->bkground.tex_y = (int)(TEX_HEIGHT * (cube->bkground.floor_y - \
		cube->bkground.cell_y)) & (TEX_HEIGHT - 1);
		cube->bkground.floor_x += cube->bkground.step_x;
		cube->bkground.floor_y += cube->bkground.step_y;
		draw_pixel(cube, x, y);
	}
}

void	raycast_floor_ceiling(t_cube *cube)
{
	int	y;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		init_camera(cube, y);
		init_dir(cube);
		find_texture(cube, y);
		y++;
	}
}
