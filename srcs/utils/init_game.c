/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:43:30 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/15 13:48:10 by bperriol         ###   ########lyon.fr   */
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
		write(2, E_MLX_WINDOW, ft_strlen(E_MLX_WINDOW));
		free(cube->vars.mlx_ptr);
		return (EXIT_FAILURE);
	}
	cube->data.img = mlx_new_image(cube->vars.mlx_ptr, \
	SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!cube->data.img)
	{
		write(2, E_XPM_IMAGE, ft_strlen(E_XPM_IMAGE));
		mlx_destroy_window(cube->vars.mlx_ptr, cube->vars.mlx_win);
		free(cube->vars.mlx_ptr);
		return (EXIT_FAILURE);
	}
	cube->data.addr = mlx_get_data_addr(cube->data.img, \
	&cube->data.bits_per_pixel, &cube->data.line_length, \
	&cube->data.endian);
	return (EXIT_SUCCESS);
}

static int	**init_textures(void)
{
	int	**textures;
	int	i;

	textures = malloc(sizeof(int *) * (NB_TEXTURES + 1));
	if (!textures)
		return (perror("Init_textures - Malloc"), NULL);
	i = 0;
	while (i < NB_TEXTURES)
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

int	init_game(t_cube *cube)
{
	if (init_mlx(cube))
		return (EXIT_FAILURE);
	cube->tex.texture = init_textures();
	if (!cube->tex.texture)
		exit_game(cube, 1);
	if (generate_textures(cube))
		exit_game(cube, 1);
	return (EXIT_SUCCESS);
}
