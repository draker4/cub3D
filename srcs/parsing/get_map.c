/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:30:55 by bboisson          #+#    #+#             */
/*   Updated: 2023/02/17 09:34:48 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	**mapjoin(char **s1, char *s2)
{
	char	**new;
	int		i;

	new = malloc(sizeof(char *) * (split_size(s1) + 2));
	if (new == NULL)
		return (free(s1), perror("mapjoin - malloc"), NULL);
	i = 0;
	while (s1 && s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	new[i++] = s2;
	new[i] = NULL;
	if (s1)
		free(s1);
	return (new);
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

int	confirm_map(t_cube *cube, int y, int x)
{
	if (y == 0 || x == 0 || y == cube->parse.max.y || x == cube->parse.max.x - 1
		|| x >= cube->parse.max.x_prev || x >= cube->parse.max.x_next)
		return (ft_error(E_WALL), EXIT_FAILURE);
	if (cube->parse.map[y - 1][x] == ' ' || cube->parse.map[y + 1][x] == ' '
	|| cube->parse.map[y][x - 1] == ' ' || cube->parse.map[y][x + 1] == ' ')
		return (ft_error(E_WALL), EXIT_FAILURE);
	if ((cube->parse.map[y][x] == '3' || cube->parse.map[y][x] == '4')
	&& ((cube->parse.map[y - 1][x] == '1' && cube->parse.map[y + 1][x] == '1')
	|| (cube->parse.map[y][x - 1] == '1' && cube->parse.map[y][x + 1] == '1')))
		return (EXIT_SUCCESS);
	else if (cube->parse.map[y][x] == '3' || cube->parse.map[y][x] == '4')
		return (ft_error(E_DOOR), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	parse_map(t_cube *cube)
{
	int			x;
	int			y;

	y = 0;
	cube->parse.max.y = split_size(cube->parse.map);
	while (cube->parse.map[y])
	{
		x = 0;
		define_limits(&cube->parse.max, cube->parse.map, y);
		while (cube->parse.map[y][x])
		{
			if (parse_cell(cube, y, x))
				return (EXIT_FAILURE);
			if ((cube->parse.map[y][x] == '0' || cube->parse.map[y][x] == '2'
			|| cube->parse.map[y][x] == '3' || cube->parse.map[y][x] == '4')
			&& confirm_map(cube, y, x))
				return (EXIT_FAILURE);
			x++;
		}
		y++;
	}
	if (cube->player.pos_x == -1)
		return (ft_error(E_NO_START), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	get_map(t_cube *cube, int fd)
{
	while (cube->parse.line[0] != '\0')
	{
		cube->parse.map = mapjoin(cube->parse.map, cube->parse.line);
		if (!cube->parse.map)
			return (EXIT_FAILURE);
		if (get_file_line(fd, &cube->parse.line))
			return (EXIT_FAILURE);
	}
	if (parse_map(cube) || map_to_int(cube))
		return (EXIT_FAILURE);
	cube->limits.y = cube->parse.max.y;
	return (EXIT_SUCCESS);
}
