/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:30:55 by bboisson          #+#    #+#             */
/*   Updated: 2023/02/14 17:08:39 by bboisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	file_type(char *str, char *type)
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
