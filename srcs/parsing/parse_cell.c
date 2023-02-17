/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:30:55 by bboisson          #+#    #+#             */
/*   Updated: 2023/02/17 14:11:29 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	choose_obj(t_cube *cube, int y, int x, t_obj **new)
{
	if (cube->parse.map[y][x] == 'L')
		*new = new_obj((t_obj){(double)x + 0.5, (double)y + 0.5, 6, 0.0, 1, 1,
				-256, 1, 0, 0, NULL}, cube, '0');
	else if (cube->parse.map[y][x] == 'B')
		*new = new_obj((t_obj){(double)x + 0.5, (double)y + 0.5, 7, 0.0, 1, 1,
				256, 1, 0, 0, NULL}, cube, '2');
	else if (cube->parse.map[y][x] == 'P')
		*new = new_obj((t_obj){(double)x + 0.5, (double)y + 0.5, 8, 0.0, 0.6,
				0.6, 0, 1, 0, 0, NULL}, cube, '2');
	else if (cube->parse.map[y][x] == '3')
		*new = new_obj((t_obj){(double)x + 0.5, (double)y + 0.5, 10, 0.0, 1, 1,
				256, 0, 0, 0, NULL}, cube, '3');
	else if (cube->parse.map[y][x] == '4')
		*new = new_obj((t_obj){(double)x + 0.5, (double)y + 0.5, 10, 0.0, 1, 1,
				256, 1, 0, TIME_ANIM, NULL}, cube, '4');
	else if (cube->parse.map[y][x] == 'G')
		*new = new_obj((t_obj){(double)x + 0.5, (double)y + 0.5, 17, 0.0, 1, 1,
				0, 1, 0, 0, NULL}, cube, '0');
	else if (cube->parse.map[y][x] == 'X')
		*new = new_obj((t_obj){(double)x + 0.5, (double)y + 0.5, 18, 0.0, 1, 1,
				256, 1, 0, TIME_ANIM, NULL}, cube, '0');
}

static int	parse_obj(t_cube *cube, int y, int x)
{
	t_obj	*new;

	new = NULL;
	choose_obj(cube, y, x, &new);
	if (!new)
		return (EXIT_FAILURE);
	obj_add_back(&cube->obj, new);
	return (EXIT_SUCCESS);
}

static int	player_start(t_cube *cube, int y, int x)
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
		|| cube->parse.map[y][x] == 'P' || cube->parse.map[y][x] == '3'
		|| cube->parse.map[y][x] == '4' || cube->parse.map[y][x] == 'G'
		|| cube->parse.map[y][x] == 'X')
		return (parse_obj(cube, y, x));
	return (ft_error(E_CELL), EXIT_FAILURE);
}
