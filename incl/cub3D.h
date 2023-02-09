/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:01:06 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/09 12:08:21 by bboisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <mlx.h>
# include <math.h>
# include <X11/X.h>
# include <stdio.h>
# include <sys/time.h>

# define SCREEN_WIDTH 2000
# define SCREEN_HEIGHT 1000
# define SCREEN_TITLE "****CUB3D BAPT'S TEAM****"
# define MOVE_SPEED 5.0
# define ROT_SPEED 3.0

# define E_ARG_NB "Select one map only\n"

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
	float	pos_x;
	float	pos_y;
	float	dir_x;
	float	dir_y;
	float	prev_dir_x;
	float	prev_dir_y;
	float	plane_x;
	float	plane_y;
}	t_player;

// typedef struct s_sprite
// {
// }	t_sprite;

typedef struct s_vars
{
	void	*mlx_ptr;
	void	*mlx_win;
}	t_vars;

typedef struct s_raycast
{
	float	camera_x;
	float	ray_dir_x;
	float	ray_dir_y;
	int		map_x;
	int		map_y;
	float	delta_dist_x;
	float	delta_dist_y;
	float	hit;
	int		step_x;
	int		step_y;
	float	side_dist_x;
	float	side_dist_y;
	int		side;
	float	dist_plan_wall;
	int		line_height;
	int		line_start;
	int		line_end;
	int		color;
}	t_raycast;

typedef struct s_frame
{
	double	frame_time;
	double	time_prev;
	double	time_now;
}	t_frame;

typedef struct s_move
{
	float	move_speed;
	float	rotate_speed;
	int		up;
	int		down;
	int		left;
	int		right;
}	t_move;

typedef struct s_cube
{
	int				**map;
	t_player		player;
	t_raycast		raycast;
	t_frame			frame;
	// t_sprite		*sprites;
	t_vars			vars;
	t_data			data;
	t_move			move;
}	t_cube;

// prototypes init_cube
int		init_cube(t_cube *cube);

// prototypes get time
double	get_time(void);

//prototypes raycasting
void	raycasting(t_cube *cube);

// prototypes mlx utils
void	draw_line(t_cube *cube, int x);
int		create_trgb(int t, int r, int g, int b);

// prototypes handle events
int		handle_keypress(int keycode, t_cube *cube);

// prototypes play game
void	play_game(t_cube *cube);

#endif
