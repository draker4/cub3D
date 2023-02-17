/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:30:55 by bboisson          #+#    #+#             */
/*   Updated: 2023/02/17 09:32:57 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	while (*id && *str && id[i] && str[i] && id[i] == str[i])
		i++;
	if (!id[i] && !str[i])
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	colour_to_int(t_cube *cube, char **tmp)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	if (rgb_format(tmp[1]) != 2)
		return (EXIT_FAILURE);
	rgb = ft_split(tmp[1], ',');
	if (!rgb)
		return (EXIT_FAILURE);
	if (split_size(rgb) != 3)
		return (EXIT_FAILURE);
	if (color_atoi(rgb[0], &r))
		return (EXIT_FAILURE);
	if (color_atoi(rgb[1], &g))
		return (EXIT_FAILURE);
	if (color_atoi(rgb[2], &b))
		return (EXIT_FAILURE);
	if (tmp[0][0] == 'F')
		cube->elem.floor_color = combine_rgb(r, g, b);
	if (tmp[0][0] == 'C')
		cube->elem.ceiling_color = combine_rgb(r, g, b);
	free_split(rgb);
	return (EXIT_SUCCESS);
}

int	confirm_elem(t_cube *cube, char **tmp)
{
	if (!confirm_id("NO", tmp[0]) && !cube->elem.north && !remove_n(tmp)
		&& !file_type(tmp[1], ".xpm"))
		cube->elem.north = tmp[1];
	else if (!confirm_id("SO", tmp[0]) && !cube->elem.south && !remove_n(tmp)
		&& !file_type(tmp[1], ".xpm"))
		cube->elem.south = tmp[1];
	else if (!confirm_id("WE", tmp[0]) && !cube->elem.west && !remove_n(tmp)
		&& !file_type(tmp[1], ".xpm"))
		cube->elem.west = tmp[1];
	else if (!confirm_id("EA", tmp[0]) && !cube->elem.east && !remove_n(tmp)
		&& !file_type(tmp[1], ".xpm"))
		cube->elem.east = tmp[1];
	else if (!confirm_id("F", tmp[0]) && !cube->elem.floor_path
		&& cube->elem.floor_color == -1 && (!remove_n(tmp)
			&& (!colour_to_int(cube, tmp) || !file_type(tmp[1], ".xpm"))))
		cube->elem.floor_path = tmp[1];
	else if (!confirm_id("C", tmp[0]) && !cube->elem.ceiling_path
		&& cube->elem.ceiling_color == -1 && (!remove_n(tmp)
			&& (!colour_to_int(cube, tmp) || !file_type(tmp[1], ".xpm"))))
		cube->elem.ceiling_path = tmp[1];
	else
		return (EXIT_FAILURE);
	free(tmp[0]);
	free(tmp);
	return (EXIT_SUCCESS);
}

int	parse_elem(t_cube *cube, int fd, int *elem)
{
	char	**tmp;

	while (cube->parse.line[0] == '\n')
	{	
		free(cube->parse.line);
		if (get_file_line(fd, &cube->parse.line))
			return (EXIT_FAILURE);
	}
	tmp = ft_split(cube->parse.line, ' ');
	if (!tmp)
		return (perror("ft_split"), EXIT_FAILURE);
	else if (split_size(tmp) == 2 && !confirm_elem(cube, tmp))
		return ((*elem)++, EXIT_SUCCESS);
	free_split(tmp);
	ft_error(E_ELEM);
	return (EXIT_FAILURE);
}

int	get_elem(t_cube *cube, int fd)
{
	int		elem;

	if (get_file_line(fd, &cube->parse.line))
		return (EXIT_FAILURE);
	elem = 0;
	while (cube->parse.line && elem < 6)
	{
		if (parse_elem(cube, fd, &elem))
			return (EXIT_FAILURE);
		free(cube->parse.line);
		if (get_file_line(fd, &cube->parse.line))
			return (EXIT_FAILURE);
	}
	while (cube->parse.line[0] == '\n')
	{	
		free(cube->parse.line);
		if (get_file_line(fd, &cube->parse.line))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
