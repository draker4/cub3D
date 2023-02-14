/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:30:55 by bboisson          #+#    #+#             */
/*   Updated: 2023/02/14 10:54:19 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	free_map(int **map)
{
	int	i;

	i = 0;
	while (*map && map[i])
		free(map[i++]);
	free (map);
}

void	free_split(char **str)
{
	int	i;

	i = 0;
	while (*str && str[i])
		free(str[i++]);
	free (str);
}

void	free_cube(t_cube *cube)
{
	if (cube->parse.line)
		free(cube->parse.line);
	if (cube->parse.map)
		free_split(cube->parse.map);
	if (cube->map)
		free_map(cube->map);
	free(cube->elem.north);
	free(cube->elem.south);
	free(cube->elem.west);
	free(cube->elem.east);
	free(cube->elem.floor);
	free(cube->elem.ceilling);
}

void	free_tab_int(int **to_free)
{
	int	i;

	i = 0;
	while (to_free[i])
		free(to_free[i++]);
	free(to_free);
}
