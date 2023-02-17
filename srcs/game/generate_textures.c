/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 18:10:35 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/17 17:44:09 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	load(t_cube *cube, int index, char *path)
{
	t_data	data;
	int		width;
	int		height;
	int		x;
	int		y;

	data.img = mlx_xpm_file_to_image(cube->vars.mlx_ptr, path, &width, &height);
	if (!data.img)
		return (x = write(2, E_XPM_IMAGE, ft_strlen(E_XPM_IMAGE)), \
		EXIT_FAILURE);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, \
	&data.line_length, &data.endian);
	x = -1;
	while (++x < TEX_WIDTH)
	{
		y = -1;
		while (++y < TEX_HEIGHT)
		{
			cube->tex.texture[index][x * TEX_HEIGHT + y] = \
			*(unsigned int *)(data.addr + (y * data.line_length + x * \
			(data.bits_per_pixel / 8)));
		}
	}
	mlx_destroy_image(cube->vars.mlx_ptr, data.img);
	return (EXIT_SUCCESS);
}

static void	generate_background(t_cube *cube)
{
	if (cube->elem.floor_color != -1)
		fill_pixel(cube, 4, cube->elem.floor_color);
	else
	{
		load(cube, 4, cube->elem.floor_path);
		if (!cube->tex.texture[4])
			exit_game(cube, 1);
	}
	if (cube->elem.ceiling_color != -1)
		fill_pixel(cube, 5, cube->elem.ceiling_color);
	else
	{
		load(cube, 5, cube->elem.ceiling_path);
		if (!cube->tex.texture[5])
			exit_game(cube, 1);
	}
}

static int	load_weapon(t_cube *cube, int index, char *path)
{
	t_data	data;
	int		width;
	int		height;
	int		x;
	int		y;

	data.img = mlx_xpm_file_to_image(cube->vars.mlx_ptr, path, &width, &height);
	if (!data.img)
		return (x = write(2, E_XPM_IMAGE, ft_strlen(E_XPM_IMAGE)), \
		EXIT_FAILURE);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, \
	&data.line_length, &data.endian);
	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		y = -1;
		while (++y < SCREEN_HEIGHT)
		{
			cube->weapon.tex[index][x * SCREEN_HEIGHT + y] = \
			*(unsigned int *)(data.addr + (y * data.line_length + x * \
			(data.bits_per_pixel / 8)));
		}
	}
	mlx_destroy_image(cube->vars.mlx_ptr, data.img);
	return (EXIT_SUCCESS);
}

static void	generate_explosion(t_cube *cube)
{
	if (load(cube, 27, BOOM1_PATH)
		|| load(cube, 28, BOOM2_PATH) || load(cube, 29, BOOM3_PATH)
		|| load(cube, 30, BOOM4_PATH) || load(cube, 31, BOOM5_PATH)
		|| load(cube, 32, BOOM6_PATH) || load(cube, 33, BOOM7_PATH)
		|| load(cube, 34, BOOM8_PATH) || load(cube, 35, BOOM9_PATH)
		|| load(cube, 36, BOOM10_PATH))
		exit_game(cube, 1);
}

int	generate_textures(t_cube *cube)
{
	if (load(cube, 0, cube->elem.north) || load(cube, 1, cube->elem.south)
		|| load(cube, 2, cube->elem.east) || load(cube, 3, cube->elem.west)
		|| load(cube, 6, LIGHT_PATH) || load(cube, 7, BARREL_PATH)
		|| load(cube, 8, PILLAR_PATH) || load(cube, 9, DOOR_PATH)
		|| load(cube, 10, SMOKE1_PATH) || load(cube, 11, SMOKE2_PATH)
		|| load(cube, 12, SMOKE3_PATH) || load(cube, 13, SMOKE4_PATH)
		|| load(cube, 14, SMOKE5_PATH) || load(cube, 15, SMOKE6_PATH)
		|| load(cube, 16, SMOKE7_PATH) || load(cube, 17, GUN_COLLECT)
		|| load(cube, 18, ENEMY1_PATH) || load(cube, 19, ENEMY2_PATH)
		|| load(cube, 20, ENEMY3_PATH) || load(cube, 21, ENEMY4_PATH)
		|| load(cube, 22, ENEMY5_PATH) || load(cube, 23, ENEMY6_PATH)
		|| load(cube, 24, ENEMY7_PATH) || load(cube, 25, ENEMY8_PATH)
		|| load(cube, 26, DEATH_PATH))
		exit_game(cube, 1);
	generate_explosion(cube);
	generate_background(cube);
	if (load_weapon(cube, 0, PUNCH1_PATH) || load_weapon(cube, 1, PUNCH2_PATH)
		|| load_weapon(cube, 2, PUNCH3_PATH) || load_weapon(cube, 3, GUN1_PATH)
		|| load_weapon(cube, 4, GUN2_PATH) || load_weapon(cube, 5, GUN3_PATH)
		|| load_weapon(cube, 6, GUN4_PATH))
		exit_game(cube, 1);
	return (EXIT_SUCCESS);
}
