/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 18:10:35 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/15 15:19:25 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	load_texture(t_cube *cube, int index, char *path)
{
	t_data	data;
	int		width;
	int		height;
	int		x;
	int		y;

	data.img = mlx_xpm_file_to_image(cube->vars.mlx_ptr, path, &width, &height);
	if (!data.img)
		return (write(2, E_XPM_IMAGE, ft_strlen(E_XPM_IMAGE)), EXIT_FAILURE);
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

static void	fill_pixel(t_cube *cube, int index, int color)
{
	int	x;
	int	y;

	x = 0;
	while (x < TEX_WIDTH)
	{
		y = 0;
		while (y < TEX_HEIGHT)
		{
			cube->tex.texture[index][x * TEX_WIDTH + y] = color;
			y++;
		}
		x++;
	}
}

static void	generate_background(t_cube *cube)
{
	if (cube->elem.floor_color != -1)
		fill_pixel(cube, 4, cube->elem.floor_color);
	else
	{
		load_texture(cube, 4, cube->elem.floor_path);
		if (!cube->tex.texture[4])
			exit_game(cube, 1);
	}
	if (cube->elem.ceiling_color != -1)
		fill_pixel(cube, 5, cube->elem.ceiling_color);
	else
	{
		load_texture(cube, 5, cube->elem.ceiling_path);
		if (!cube->tex.texture[5])
			exit_game(cube, 1);
	}
}

int	generate_textures(t_cube *cube)
{
	if (load_texture(cube, 0, cube->elem.north)
		|| load_texture(cube, 1, cube->elem.south)
		|| load_texture(cube, 2, cube->elem.east)
		|| load_texture(cube, 3, cube->elem.west)
		|| load_texture(cube, 6, LIGHT_PATH)
		|| load_texture(cube, 7, BARREL_PATH)
		|| load_texture(cube, 8, PILLAR_PATH)
		|| load_texture(cube, 9, PUNCH3_PATH))
		exit_game(cube, 1);
	generate_background(cube);
	return (EXIT_SUCCESS);
}
