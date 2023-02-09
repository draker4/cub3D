/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cube.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:43:30 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/09 19:03:23 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	init_mlx(t_cube *cube)
{
	cube->vars.mlx_ptr = mlx_init();
	if (!cube->vars.mlx_ptr)
		return (EXIT_FAILURE);
	cube->vars.mlx_win = mlx_new_window(cube->vars.mlx_ptr, \
	SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
	if (!cube->vars.mlx_win)
	{
		free(cube->vars.mlx_ptr);
		return (EXIT_FAILURE);
	}
	cube->data.img = mlx_new_image(cube->vars.mlx_ptr, \
	SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!cube->data.img)
	{
		mlx_destroy_window(cube->vars.mlx_ptr, cube->vars.mlx_win);
		free(cube->vars.mlx_ptr);
		return (EXIT_FAILURE);
	}
	cube->data.addr = mlx_get_data_addr(cube->data.img, \
	&cube->data.bits_per_pixel, &cube->data.line_length, \
	&cube->data.endian);
	return (EXIT_SUCCESS);
}

static int	**init_buffer(void)
{
	int	**buffer;
	int	i;

	buffer = malloc(sizeof(int *) * (SCREEN_HEIGHT));
	if (!buffer)
		return (perror("Init_buffer - Malloc"), NULL);
	i = 0;
	while (i < SCREEN_HEIGHT)
	{
		buffer[i] = malloc(sizeof(int) * SCREEN_WIDTH);
		if (!buffer[i])
		{
			while (--i)
				free(buffer[i]);
			free(buffer);
			return (perror("Init_buffer - Malloc"), NULL);
		}
		i++;
	}
	return (buffer);
}

static int	**init_textures(void)
{
	int	**textures;
	int	i;

	textures = malloc(sizeof(int *) * (8 + 1));
	if (!textures)
		return (perror("Init_textures - Malloc"), NULL);
	i = 0;
	while (i < 8)
	{
		textures[i] = malloc(sizeof(int) * (TEX_WIDTH * TEX_HEIGHT));
		if (!textures[i])
		{
			while (--i)
				free(textures[i]);
			free(textures);
			return (perror("Init_textures - Malloc"), NULL);
		}
		i++;
	}
	textures[i] = NULL;
	return (textures);
}

int	init_cube(t_cube *cube)
{
	cube->player.pos_x = 22;
	cube->player.pos_y = 12;
	cube->player.dir_x = -1;
	cube->player.dir_y = 0;
	cube->player.plane_x = 0;
	cube->player.plane_y = 0.66;
	cube->move.up = 0;
	cube->move.down = 0;
	cube->move.left = 0;
	cube->move.right = 0;
	cube->move.rotate_left = 0;
	cube->move.rotate_right = 0;
	cube->frame.frame_time = 0;
	if (init_mlx(cube))
		return (EXIT_FAILURE);
	cube->buffer = init_buffer();
	if (!cube->buffer)
	{
		mlx_destroy_window(cube->vars.mlx_ptr, cube->vars.mlx_win);
		mlx_destroy_image(cube->vars.mlx_ptr, cube->data.img);
		free(cube->vars.mlx_ptr);
		return (EXIT_FAILURE);
		// egal a exit game avec exit 1
	}
	cube->tex.texture = init_textures();
	if (!cube->tex.texture)
		return (EXIT_FAILURE);
		//COMME AU DESSUS exit game avec retour 1
	generate_textures(cube);
	return (EXIT_SUCCESS);
}
