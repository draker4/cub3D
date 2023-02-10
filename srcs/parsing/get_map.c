/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:30:55 by bboisson          #+#    #+#             */
/*   Updated: 2023/02/10 17:27:46 by bboisson         ###   ########.fr       */
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

int	parse_map(t_cube *cube)
{
	int			x;
	int			y;
	t_limits	max;

	y = 0;
	max.y = split_size(cube->map);
	while (cube->map[y])
	{
		x = 0;
		define_limits(&max, cube->map, y);
		while (cube->map[y][x])
		{
			if (is_valid_cell(cube->map, y, x))
				return (EXIT_FAILURE);
			if (player_start(cube, y, x))
				return (EXIT_FAILURE);
			if (cube->map[y][x] == '0' && confirm_map(cube, max, y, x))
				return (EXIT_FAILURE);
			x++;
		}
		y++;
	}
	return (EXIT_SUCCESS);
}


int	get_map(t_cube *cube, int fd)
{
	while (cube->line[0] != '\0')
	{
		cube->map = mapjoin(cube->map, cube->line);
		if (!cube->map)
			return (EXIT_FAILURE);
		if (get_file_line(fd, &cube->line))
			return (EXIT_FAILURE);
	}
	if (parse_map(cube))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
