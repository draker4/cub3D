/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:43:30 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/14 15:12:53 by bboisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	init_player(t_cube *cube, t_player define, int y, int x)
{
	if (cube->player.pos_x != -1)
		return (ft_error(E_PLAYER), EXIT_FAILURE);
	cube->player.pos_x = x;
	cube->player.pos_y = y;
	cube->player.dir_x = define.dir_x;
	cube->player.dir_y = define.dir_y;
	cube->player.plane_x = define.plane_x;
	cube->player.plane_y = define.plane_y;
	cube->parse.map[y][x] = '0';
	return (EXIT_SUCCESS);
}

void	init_cube(t_cube *cube)
{
	cube->map = NULL;
	cube->parse.line = NULL;
	cube->parse.map = NULL;
	cube->elem.north = NULL;
	cube->elem.south = NULL;
	cube->elem.west = NULL;
	cube->elem.east = NULL;
	cube->elem.floor = NULL;
	cube->elem.ceilling = NULL;
	cube->player.pos_x = -1;
	cube->player.plane_x = 0;
	cube->player.plane_y = 0.66;
	cube->move.up = 0;
	cube->move.down = 0;
	cube->move.left = 0;
	cube->move.right = 0;
	cube->move.rotate_left = 0;
	cube->move.rotate_right = 0;
	cube->tex.texture = NULL;
	cube->buffer = NULL;
}
