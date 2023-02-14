/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 18:10:35 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/14 17:59:41 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	load_texture(t_cube *cube, int index, char *path)
{
	t_data	data;
	int		width;
	int		height;
	int		x;
	int		y;

	data.img = mlx_xpm_file_to_image(cube->vars.mlx_ptr, path, &width, &height);
	if (!data.img)
		return (cube->tex.texture[index] = NULL, \
		write(2, E_XPM_IMAGE, ft_strlen(E_XPM_IMAGE)), (void)0);
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
}

static void	generate_background(t_cube *cube)
{
	if (cube->elem.floor_colour != -1)
		cube->bkground.floor_color = cube->elem.floor_colour;
	else
	{
		load_texture(cube, 4, cube->elem.floor_path);
		if (!cube->tex.texture[4])
			exit_game(cube, 1);
	}
	if (cube->elem.ceiling_colour != -1)
		cube->bkground.ceil_color = cube->elem.ceiling_colour;
	else
	{
		load_texture(cube, 5, cube->elem.ceiling_path);
		if (!cube->tex.texture[5])
			exit_game(cube, 1);
	}
}

int	generate_textures(t_cube *cube)
{
	int	i;

	load_texture(cube, 0, cube->elem.north);
	load_texture(cube, 1, cube->elem.south);
	load_texture(cube, 2, cube->elem.east);
	load_texture(cube, 3, cube->elem.west);
	i = 0;
	while (i < 4)
	{
		if (!cube->tex.texture[i++])
			exit_game(cube, 1);
	}
	generate_background(cube);
	return (EXIT_SUCCESS);
}
