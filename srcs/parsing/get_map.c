/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:30:55 by bboisson          #+#    #+#             */
/*   Updated: 2023/02/09 17:03:31 by bboisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_map(t_cube *cube, int fd, char **data)
{
	while (data)
	{
		if (mapjoin())
			return (EXIT_FAILURE);
		if (get_file_line(fd, data))
			return (EXIT_FAILURE);
	}
	/*if (parse_map())
		return (EXIT_FAILURE);*/
	return (EXIT_SUCCESS);
}
