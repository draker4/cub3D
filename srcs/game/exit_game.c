/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:19:16 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/20 11:36:38 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	exit_game(t_cube *cube, int exit_status)
{
	free_cube(cube);
	mlx_clear_window(cube->vars.mlx_ptr, cube->vars.mlx_win);
	mlx_destroy_image(cube->vars.mlx_ptr, cube->data.img);
	mlx_destroy_window(cube->vars.mlx_ptr, cube->vars.mlx_win);
	mlx_destroy_display(cube->vars.mlx_ptr);
	free(cube->vars.mlx_ptr);
	if (exit_status != 1)
		exit_status = 0;
	exit(exit_status);
}
