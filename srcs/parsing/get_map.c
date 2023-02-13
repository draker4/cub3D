/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:30:55 by bboisson          #+#    #+#             */
/*   Updated: 2023/02/13 13:26:53 by bboisson         ###   ########.fr       */
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

	y = 0;
	cube->parse.max.y = split_size(cube->parse.map);
	while (cube->parse.map[y])
	{
		x = 0;
		define_limits(&cube->parse.max, cube->parse.map, y);
		while (cube->parse.map[y][x])
		{
			if (is_valid_cell(cube->parse.map, y, x))
				return (EXIT_FAILURE);
			if (player_start(cube, y, x))
				return (EXIT_FAILURE);
			if (cube->parse.map[y][x] == '0' && confirm_map(cube,
				cube->parse.max, y, x))
				return (EXIT_FAILURE);
			x++;
		}
		y++;
	}
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
	if (parse_map(cube))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
