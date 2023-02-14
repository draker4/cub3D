/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:30:55 by bboisson          #+#    #+#             */
/*   Updated: 2023/02/14 18:13:13 by bboisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	combine_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	colour_atoi(char *str, int *colour)
{
	int				i;

	i = 0;
	*colour = 0;
	while (str[i] >= '0' && str[i] <= '9' && *colour < 256)
	{
		*colour = *colour * 10 + str[i] - 48;
		i++;
	}
	if (str[i])
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	remove_n(char **tmp)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	while (tmp[1][i] && tmp[1][i] != '\n')
		i++;
	new = malloc(sizeof(char) * (i + 1));
	if (!new)
		return (perror("remove_n - malloc"), EXIT_FAILURE);
	j = -1;
	while (++j < i)
		new[j] = tmp[1][j];
	new[j] = '\0';
	free (tmp[1]);
	tmp[1] = new;
	return (EXIT_SUCCESS);
}

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
