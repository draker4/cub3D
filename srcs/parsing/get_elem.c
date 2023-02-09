/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:30:55 by bboisson          #+#    #+#             */
/*   Updated: 2023/02/09 18:20:02 by bboisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	split_size(char **str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

int	confirm_id(char *id, char *str)
{
	int		i;
	int		size_id;
	int		size_str;

	if (!str)
		return (EXIT_FAILURE);
	size_id = ft_strlen(id);
	size_str = ft_strlen(str);
	if (size_id != size_str)
		return (EXIT_FAILURE);
	i = 0;
	while (id[i] == str[i] && id[i] && str[i])
		i++;
	if (i == size_id && size_str == size_str)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}


int	confirm_elem(t_cube *cube, char **tmp)
{
	if (confirm_id("NO", tmp[0]) && !cube->elem.north)
		cube->elem.north = tmp[1];
	else if (confirm_id("SO", tmp[0]) && !cube->elem.south)
		cube->elem.south = tmp[1];
	else if (confirm_id("WE", tmp[0]) && !cube->elem.west)
		cube->elem.west = tmp[1];
	else if (confirm_id("EA", tmp[0]) && !cube->elem.east)
		cube->elem.east = tmp[1];
	else if (confirm_id("F", tmp[0]) && !cube->elem.floor)
		cube->elem.floor = tmp[1];
	else if (confirm_id("C", tmp[0]) && !cube->elem.ceilling)
		cube->elem.ceilling = tmp[1];
	else
		return (EXIT_FAILURE);
	free(tmp[0]);
	free(tmp);
	return (EXIT_SUCCESS);
}

int	parse_elem(t_cube *cube, int fd, char **data)
{
	char	**tmp;

	while ((*data)[0] == '\n')
	{	
		free(*data);
		if (get_file_line(fd, data))
			return (EXIT_FAILURE);
	}
	tmp = ft_split(*data, ' ');
	if (!tmp)
		return (perror("ft_split"), EXIT_FAILURE);
	else if (split_size(tmp) == 2 && !confirm_elem(cube, tmp))
		return (EXIT_SUCCESS);
	free_split(tmp);
	ft_error(E_ELEM);
	return (EXIT_FAILURE);
}

int	get_elem(t_cube *cube, int fd, char **data)
{
	int		elem;

	if (get_file_line(fd, data))
		return (EXIT_FAILURE);
	elem = 0;
	while (*data && elem < 6)
	{
		if (parse_elem(cube, fd, data))
			return (free(*data), EXIT_FAILURE);
		free(*data);
		if (get_file_line(fd, data))
			return (EXIT_FAILURE);
	}
	while ((*data)[0] == '\n')
	{	
		free(*data);
		if (get_file_line(fd, data))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}