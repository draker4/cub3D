/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:30:55 by bboisson          #+#    #+#             */
/*   Updated: 2023/02/15 15:24:44 by bboisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_valid_cell(char **map, int y, int x)
{
	if (map[y][x] == ' ' || map[y][x] == '0' || map[y][x] == '1'
	|| map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'W'
	|| map[y][x] == 'E' || (x > 0 && map[y][x] == '\n')
	|| map[y][x] == 'B' || map[y][x] == 'L' || map[y][x] == 'P')
		return (EXIT_SUCCESS);
	return (ft_error(E_CELL), EXIT_FAILURE);
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

void	define_limits(t_limits *max, char **map, int y)
{
	if (y <= 0)
		max->x_prev = 0;
	else
		max->x_prev = ft_strlen(map[y - 1]) - 1;
	max->x = ft_strlen(map[y]) - 1;
	if (y == max->y)
		max->x_next = 0;
	else
		max->x_next = ft_strlen(map[y + 1]) - 1;
}

int	confirm_map(t_cube *cube, t_limits max, int y, int x)
{
	if (y == 0 || x == 0 || y == max.y || x == max.x || x >= max.x_prev
		|| x >= max.x_next)
		return (ft_error(E_WALL), EXIT_FAILURE);
	if (cube->parse.map[y - 1][x] == ' ' || cube->parse.map[y + 1][x] == ' '
	|| cube->parse.map[y][x - 1] == ' ' || cube->parse.map[y][x + 1] == ' ')
		return (ft_error(E_WALL), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
