/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:30:55 by bboisson          #+#    #+#             */
/*   Updated: 2023/02/16 16:03:46 by bboisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

size_t	line_size(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

int	largest_line(t_cube *cube)
{
	int	i;
	int	line;
	int	size_max;

	i = 0;
	size_max = 0;
	while (cube->parse.map[i])
	{
		line = line_size(cube->parse.map[i]);
		if (line > size_max)
			size_max = line;
		i++;
	}
	return (size_max);
}

int	line_to_int(t_cube *cube, int i, int size_max)
{
	int	j;

	j = 0;
	cube->map[i] = malloc(sizeof(int) * (size_max + 1));
	if (!cube->map[i])
		return (perror("line_to_int - malloc"), EXIT_FAILURE);
	while (cube->parse.map[i][j] && cube->parse.map[i][j] != '\n')
	{
		if (cube->parse.map[i][j] == ' ')
			cube->map[i][j] = -1;
		else
			cube->map[i][j] = cube->parse.map[i][j] - 48;
		j++;
	}
	while (j < size_max)
		cube->map[i][j++] = -1;
	cube->map[i][j] = '\0';
	return (EXIT_SUCCESS);
}

int	map_to_int(t_cube *cube)
{
	int	i;
	int	size_max;

	i = 0;
	cube->map = malloc(sizeof(int *) * (split_size(cube->parse.map) + 1));
	if (!cube->map)
		return (perror("map_to_int - malloc"), EXIT_FAILURE);
	size_max = largest_line(cube);
	cube->limits.x = size_max;
	while (cube->parse.map[i] && cube->parse.map[i][0] != '\0')
	{
		cube->map[i + 1] = NULL;
		if (line_to_int(cube, i, size_max))
			return (EXIT_FAILURE);
		i++;
	}
	cube->parse.map[i] = NULL;
	return (EXIT_SUCCESS);
}
