/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:30:55 by bboisson          #+#    #+#             */
/*   Updated: 2023/02/13 14:35:43 by bboisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_valid_cell(char **map, int y, int x)
{
	if (map[y][x] == ' ' || map[y][x] == '0' || map[y][x] == '1'
	|| map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'W'
	|| map[y][x] == 'E' || (x > 0 && map[y][x] == '\n'))
		return (EXIT_SUCCESS);
	return (ft_error(E_CELL), EXIT_FAILURE);
}

int	define_player_start(t_cube *cube, int y, int x)
{
	if (cube->player.pos_x != -1)
		return (ft_error(E_PLAYER), EXIT_FAILURE);
	cube->player.pos_x = x;
	cube->player.pos_y = y;
	if (cube->parse.map[y][x] == 'N')
	{
		cube->player.dir_y = -1;
		cube->player.dir_x = 0;
	}
	else if (cube->parse.map[y][x] == 'S')
	{
		cube->player.dir_y = 1;
		cube->player.dir_x = 0;
	}
	else if (cube->parse.map[y][x] == 'W')
	{
		cube->player.dir_y = 0;
		cube->player.dir_x = -1;
	}
	else if (cube->parse.map[y][x] == 'E')
	{
		cube->player.dir_y = 0;
		cube->player.dir_x = 1;
	}
	return (cube->parse.map[y][x] = '0', EXIT_SUCCESS);
}

int	player_start(t_cube *cube, int y, int x)
{
	if (cube->parse.map[y][x] == 'N')
		return (define_player_start(cube, y, x));
	else if (cube->parse.map[y][x] == 'S')
		return (define_player_start(cube, y, x));
	else if (cube->parse.map[y][x] == 'W')
		return (define_player_start(cube, y, x));
	else if (cube->parse.map[y][x] == 'E')
		return (define_player_start(cube, y, x));
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
		return (EXIT_FAILURE);
	if (cube->parse.map[y - 1][x] == ' ' || cube->parse.map[y + 1][x] == ' '
	|| cube->parse.map[y][x - 1] == ' ' || cube->parse.map[y][x + 1] == ' ')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
