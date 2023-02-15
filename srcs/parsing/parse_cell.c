/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:30:55 by bboisson          #+#    #+#             */
/*   Updated: 2023/02/15 17:20:46 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	parse_obj(t_cube *cube, int y, int x)
{
	t_obj	*new;

	new = NULL;
	if (cube->parse.map[y][x] == 'L')
		new = new_obj((t_obj){0, 0, 6, 0.0, 1, 1, -256, NULL}, y, x);
	else if (cube->parse.map[y][x] == 'B')
		new = new_obj((t_obj){0, 0, 7, 0.0, 1, 1, 256, NULL}, y, x);
	else if (cube->parse.map[y][x] == 'P')
		new = new_obj((t_obj){0, 0, 8, 0.0, 1, 1, 256, NULL}, y, x);
	if (!new)
		return (EXIT_FAILURE);
	obj_add_back(&cube->obj, new);
	cube->parse.map[y][x] = '0';
	return (EXIT_SUCCESS);
}

int	player_start(t_cube *cube, int y, int x)
{
	if (cube->parse.map[y][x] == 'N')
		return (init_player(cube, (t_player){0, 0, 0, -1, ANGLE, 0}, y, x));
	else if (cube->parse.map[y][x] == 'S')
		return (init_player(cube, (t_player){0, 0, 0, 1, -ANGLE, 0}, y, x));
	else if (cube->parse.map[y][x] == 'W')
		return (init_player(cube, (t_player){0, 0, -1, 0, 0, -ANGLE}, y, x));
	else if (cube->parse.map[y][x] == 'E')
		return (init_player(cube, (t_player){0, 0, 1, 0, 0, ANGLE}, y, x));
	return (EXIT_SUCCESS);
}

int	parse_cell(t_cube *cube, int y, int x)
{
	if (cube->parse.map[y][x] == ' ' || cube->parse.map[y][x] == '0'
		|| cube->parse.map[y][x] == '1'
		|| (x > 0 && cube->parse.map[y][x] == '\n'))
		return (EXIT_SUCCESS);
	if (cube->parse.map[y][x] == 'N' || cube->parse.map[y][x] == 'S'
		|| cube->parse.map[y][x] == 'W' || cube->parse.map[y][x] == 'E')
		return (player_start(cube, y, x));
	if (cube->parse.map[y][x] == 'B' || cube->parse.map[y][x] == 'L'
		|| cube->parse.map[y][x] == 'P')
		return (parse_obj(cube, y, x));
	return (ft_error(E_CELL), EXIT_FAILURE);
}