/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:30:55 by bboisson          #+#    #+#             */
/*   Updated: 2023/02/14 17:07:05 by bboisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_data(t_cube *cube, char *file)
{
	int		fd;

	init_cube(cube);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror("Error\nget_map - open"), EXIT_FAILURE);
	if (get_elem(cube, fd) || get_map(cube, fd))
		return (EXIT_FAILURE);
	close(fd);
	if (fd == -1)
		return (perror("Error\nget_map - close"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
