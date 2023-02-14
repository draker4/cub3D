/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:19:16 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/14 10:51:12 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	exit_game(t_cube *cube, int exit_status)
{
	free_cube(cube);
	if (cube->tex.texture)
		free_tab_int(cube->tex.texture);
	if (cube->buffer)
		free_tab_int(cube->buffer);
	mlx_clear_window(cube->vars.mlx_ptr, cube->vars.mlx_win);
	mlx_destroy_image(cube->vars.mlx_ptr, cube->data.img);
	mlx_destroy_window(cube->vars.mlx_ptr, cube->vars.mlx_win);
	free(cube->vars.mlx_ptr);
	exit(exit_status);
}
