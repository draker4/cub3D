/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:56:17 by bboisson          #+#    #+#             */
/*   Updated: 2023/02/10 16:47:32 by bboisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// strjoin with the s1 being free at the end;
static char	*ft_str_join(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;

	new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (new == NULL)
		return (free(s1), perror("ft_str_join - malloc"), NULL);
	i = 0;
	while (s1 && s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		new[i + j] = s2[j];
		j++;
	}
	new[i + j] = '\0';
	if (s1)
		free(s1);
	return (new);
}

int	get_file_line(int fd, char **line)
{
	char	str[2];
	int		nbc;

	*line = NULL;
	nbc = 1;
	str[0] = '\0';
	while (!ft_strchr(str, '\n') && nbc > 0)
	{
		nbc = read(fd, str, 1);
		if (nbc < 0)
			return (free(*line), perror("get_file_line - read"), EXIT_FAILURE);
		str[nbc] = '\0';
		*line = ft_str_join(*line, str);
		if (!*line)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
