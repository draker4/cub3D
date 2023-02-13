/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:30:55 by bboisson          #+#    #+#             */
/*   Updated: 2023/02/13 14:33:45 by bboisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	map_to_int(t_cube *cube)
{
	int	i;
	int	j;

	i = 0;
	cube->map = malloc(sizeof(int *) * (split_size(cube->parse.map)) + 1);
	if (!cube->map)
		return (perror("map_to_int - malloc"), EXIT_FAILURE);
	while (cube->parse.map[i])
	{
		j = 0;
		cube->map[i] = malloc(sizeof(int) * (ft_strlen(cube->parse.map[i])) + 1);
		if (!cube->map[i])
			return (perror("map_to_int - malloc"), EXIT_FAILURE);
		while (cube->parse.map[i][j])
		{
			if (cube->parse.map[i][j] == ' ')
				cube->map[i][j] = 0;
			else
				cube->map[i][j] = cube->parse.map[i][j] - 48;
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
