/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 18:10:35 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/14 13:23:26 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// static void	swap_x_y(t_cube *cube)
// {
// 	int	i;
// 	int	x;
// 	int	y;
// 	int	tmp;

// 	i = 0;
// 	while (i < 8)
// 	{
// 		x = 0;
// 		while (x < TEX_WIDTH)
// 		{
// 			y = 0;
// 			while (y < x)
// 			{
// 				tmp = cube->tex.texture[i][TEX_WIDTH * y + x];
// 				cube->tex.texture[i][TEX_WIDTH * y + x] = \
// 				cube->tex.texture[i][TEX_WIDTH * x + y];
// 				cube->tex.texture[i][TEX_WIDTH * x + y] = tmp;
// 				y++;
// 			}
// 			x++;
// 		}
// 		i++;
// 	}
// }

//juste premier test, il faudra changer avec les paths des textures ici cets juste pour generer en attendant

// void	generate_textures(t_cube *cube)
// {
// 	int	x;
// 	int	y;

// 	x = 0;
// 	while (x < TEX_WIDTH)
// 	{
// 		y = 0;
// 		while (y < TEX_HEIGHT)
// 		{
// 			int xorcolor = (x * 256 / TEX_WIDTH) ^ (y * 256 / TEX_HEIGHT);
// 			//int xcolor = x * 256 / TEX_WIDTH;
// 			int ycolor = y * 256 / TEX_HEIGHT;
// 			int xycolor = y * 128 / TEX_HEIGHT + x * 128 / TEX_WIDTH;
// 			cube->tex.texture[0][TEX_WIDTH * y + x] = 65534 * 254 * (x != y && x != TEX_WIDTH - y); //flat red texture with black cross
// 			cube->tex.texture[1][TEX_WIDTH * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
// 			cube->tex.texture[2][TEX_WIDTH * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
// 			cube->tex.texture[3][TEX_WIDTH * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
// 			cube->tex.texture[4][TEX_WIDTH * y + x] = 256 * xorcolor; //xor green
// 			cube->tex.texture[5][TEX_WIDTH * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
// 			cube->tex.texture[6][TEX_WIDTH * y + x] = 65536 * ycolor; //red gradient
// 			cube->tex.texture[7][TEX_WIDTH * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
// 			y++;
// 		}
// 		x++;
// 	}
// 	swap_x_y(cube);
// }

static void	load_texture(t_cube *cube, int	index, char *path)
{
	t_data	data;
	int		width;
	int		height;
	int		x;
	int		y;

	data.img = mlx_xpm_file_to_image(cube->vars.mlx_ptr, path, \
	&width, &height);
	if (!data.img)
	{
		write(2, E_XPM_IMAGE, ft_strlen(E_XPM_IMAGE));
		cube->tex.texture[index] = NULL;
		return ;
	}
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, \
	&data.line_length, &data.endian);
	x = 0;
	while (x < TEX_WIDTH)
	{
		y = 0;
		while (y < TEX_HEIGHT)
		{
			cube->tex.texture[index][x * TEX_HEIGHT + y] = *(unsigned int *)(data.addr + (y * data.line_length + x * \
			(data.bits_per_pixel / 8)));
			y++;
		}
		x++;
	}
	mlx_destroy_image(cube->vars.mlx_ptr, data.img);
}

int	generate_textures(t_cube *cube)
{
	int	i;

	load_texture(cube, 0, "./textures/eagle.xpm");
	load_texture(cube, 1, "./textures/greystone.xpm");
	load_texture(cube, 2, "./textures/redbrick.xpm");
	load_texture(cube, 3, "./textures/purplestone.xpm");
	i = 0;
	while (i < 4)
	{
		if (!cube->tex.texture[i++])
			exit_game(cube, 1);
	}
	return (EXIT_SUCCESS);
}
