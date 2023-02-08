/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:01:06 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/08 14:59:05 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <mlx.h>
# include <math.h>

#define screenWidth 1000
#define screenHeight 600
#define mapWidth 24
#define mapHeight 24

typedef struct s_point
{
	int	x;
	int	y;
	int	color;
}	t_point;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_player
{
	int	pos_x;
	int	pos_y;
	int	dir_x;
	int	dir_y;
}	t_player;

// typedef struct s_sprite
// {
// }	t_sprite;

typedef struct s_vars
{
	void	*mlx_ptr;
	void	*mlx_win;
}	t_vars;

typedef struct s_cub3D
{
	int			**map;
	t_player	*player;
	// t_sprite	*sprites;
	t_vars		*vars;
	t_data		*data;
}	t_cub3D;


double	get_time(void);

#endif
