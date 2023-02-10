/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:30:55 by bboisson          #+#    #+#             */
/*   Updated: 2023/02/10 15:20:11 by bboisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_valid_cell(char **map, int x, int y)
{
	if (map[x][y] != ' ' || map[x][y] != '0' || map[x][y] != '1'
	|| map[x][y] != 'N' || map[x][y] != 'S' || map[x][y] != 'W'
	|| map[x][y] != 'E')
		return (ft_error(E_CELL), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	define_player_start(t_cube *cube, int x, int y)
{
	if (cube->player.pos_x != -1)
		return (ft_error(E_PLAYER), EXIT_FAILURE);
	cube->player.pos_x = x;
	cube->player.pos_y = y;
	if (cube->map[x][y] == 'N')
	{
		cube->player.dir_x = 0;
		cube->player.dir_y = -1;
	}
	else if (cube->map[x][y] != 'S')
	{
		cube->player.dir_x = 0;
		cube->player.dir_y = 1;
	}
	else if (cube->map[x][y] != 'W')
	{
		cube->player.dir_x = -1;
		cube->player.dir_y = 0;
	}
	else if (cube->map[x][y] != 'E')
	{
		cube->player.dir_x = 1;
		cube->player.dir_y = 0;
	}
	return (EXIT_SUCCESS);
}

int	player_start(t_cube *cube, int x, int y)
{
	if (cube->map[x][y] != 'N')
		return (define_player_start(cube, x, y));
	else if (cube->map[x][y] != 'S')
		return (define_player_start(cube, x, y));
	else if (cube->map[x][y] != 'W')
		return (define_player_start(cube, x, y));
	else if (cube->map[x][y] != 'E')
		return (define_player_start(cube, x, y));
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

int	confirm_map(t_cube *cube, t_limits max, int x, int y)
{
	if (y == 0 || x == 0 || y == max.y || x == max.x || x >= max.x_prev
		|| x >= max.x_next)
		return (EXIT_FAILURE);
	else if (cube->map[y - 1][x] == ' ' || cube->map[y + 1][x] == ' '
	|| cube->map[y][x - 1] == ' ' || cube->map[y][x + 1] == ' ')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
