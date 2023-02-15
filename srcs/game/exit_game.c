/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:19:16 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/15 14:59:12 by bboisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	exit_game(t_cube *cube, int exit_status)
{
	free_cube(cube);
	mlx_clear_window(cube->vars.mlx_ptr, cube->vars.mlx_win);
	mlx_destroy_image(cube->vars.mlx_ptr, cube->data.img);
	mlx_destroy_window(cube->vars.mlx_ptr, cube->vars.mlx_win);
	free(cube->vars.mlx_ptr);
	if (exit_status != 1)
		exit_status = 0;
	exit(exit_status);
}
