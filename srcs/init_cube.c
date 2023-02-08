/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cube.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:43:30 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/08 19:40:25 by bperriol         ###   ########lyon.fr   */
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
		free(cube->vars.mlx_ptr);
		free(cube->vars.mlx_win);
		return (EXIT_FAILURE);
	}
	cube->data.addr = mlx_get_data_addr(cube->data.img, \
	&cube->data.bits_per_pixel, &cube->data.line_length, \
	&cube->data.endian);
	return (EXIT_SUCCESS);
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
	if (!init_mlx(cube))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
