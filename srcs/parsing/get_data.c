/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:30:55 by bboisson          #+#    #+#             */
/*   Updated: 2023/02/09 17:03:46 by bboisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	map_type(char *str, char *type)
{
	int	i;
	int	j;

	i = ft_strlen(str);
	j = ft_strlen(type);
	while (i >= 0 && j >= 0)
	{
		if (str[i] != type[j])
			return (EXIT_FAILURE);
		i--;
		j--;
	}
	if (j < 0)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	get_data(t_cube *cube, char *file)
{
	int		fd;
	char	*data;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror("Error\nget_map - open"), EXIT_FAILURE);
	if (get_elem(cube, fd, &data) || get_map(cube, fd, &data))
		return (EXIT_FAILURE);
	close(fd);
	if (fd == -1)
		return (perror("Error\nget_map - close"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
