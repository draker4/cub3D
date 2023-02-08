/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:38:16 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/08 18:20:01 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

static void	my_mlx_pixel_put(t_cube *cube, int x)
{
	char	*dst;

	dst = cube->data.addr + (cube->raycast.line_start * \
	cube->data.line_length + x * (cube->data.bits_per_pixel / 8));
	*(unsigned int *)dst = cube->raycast.color;
}

void	draw_line(t_cube *cube, int x)
{
	while (cube->raycast.line_start <= cube->raycast.line_end)
	{
		my_mlx_pixel_put(cube, x);
		cube->raycast.line_start++;
	}
}
