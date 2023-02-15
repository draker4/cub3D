/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:01:06 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/15 15:18:58 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <fcntl.h>
# include <mlx.h>
# include <math.h>
# include <X11/X.h>
# include <stdio.h>
# include <sys/time.h>

# define SCREEN_WIDTH 2000
# define SCREEN_HEIGHT 1000
# define SCREEN_TITLE "****CUB3D BAPT'S TEAM****"
# define TEX_WIDTH 256
# define TEX_HEIGHT 256
# define MOVE_SPEED 4.0
# define ROT_SPEED 2.0
# define WALL_HEIGHT 1.5
# define ANGLE 0.66
# define NB_SPRITES 20
# define NB_TEXTURES 10

# define E_ARG_NB "Select one map only\n"
# define E_CELL "Forbidden cell type used\n"
# define E_ELEM "The data elements have to be check\n"
# define E_FILE_TYPE "The map should be of type .cub\n"
# define E_PLAYER "Player starting position define more than once\n"
# define E_NO_START "No starting position defined\n"
# define E_WALL "The map isn't closed or there is an empty field between \
the wall\n"
# define E_XPM_IMAGE "Mlx_xpm_file_to_image function error\n"
# define E_MLX_WINDOW "Mlx_new_window function error\n"

# define LIGHT_PATH "./sprites/greenlight.xpm"
# define BARREL_PATH "./sprites/barrel.xpm"
# define PILLAR_PATH "./sprites/pillar.xpm"
# define PUNCH3_PATH "./sprites/punch3.xpm"

/* ------------------------------  STRUCTURE  ------------------------------- */

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
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_sprite
{
	double	pos_x;
	double	pos_y;
	int		texture;
	double	distance;
	double	u_div;
	double	v_div;
	double	v_move;
}	t_sprite;

typedef struct s_sprites
{
	double	sprite_x;
	double	sprite_y;
	double	inv_mat;
	double	transf_x;
	double	transf_y;
	double	sp_height;
	double	sp_width;
	int		sp_screen_x;
	int		start_y;
	int		end_y;
	int		start_x;
	int		end_x;
	int		tex_x;
	int		tex_y;
	int		color;
	int		d;
	int		move_screen;
}	t_sprites;

typedef struct s_vars
{
	void	*mlx_ptr;
	void	*mlx_win;
}	t_vars;

typedef struct s_raycast
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	hit;
	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;
	int		side;
	double	dist_plan_wall;
	int		line_height;
	int		line_start;
	int		line_end;
}	t_raycast;

typedef struct s_frame
{
	double	frame_time;
	double	time_prev;
	double	time_now;
}	t_frame;

typedef struct s_move
{
	double	move_speed;
	double	rotate_speed;
	int		up;
	int		down;
	int		left;
	int		right;
	int		rotate_right;
	int		rotate_left;
}	t_move;

typedef struct s_elem
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	int		floor_color;
	int		ceiling_color;
	char	*floor_path;
	char	*ceiling_path;
}	t_elem;

typedef struct s_limits
{
	int		y;
	int		x;
	int		x_prev;
	int		x_next;
}	t_limits;

typedef struct s_parse
{
	char		*line;
	char		**map;
	t_limits	max;
}	t_parse;

typedef struct s_tex
{
	int		**texture;
	int		tex_num;
	int		tex_x;
	int		tex_y;
	int		color;
	double	step;
	double	tex_pos;
	double	wall_hit_x;
}	t_tex;

typedef struct s_bkground
{
	float	ray_dir_x0;
	float	ray_dir_x1;
	float	ray_dir_y0;
	float	ray_dir_y1;
	int		center_y;
	float	pos_z;
	float	hori_dist;
	float	step_x;
	float	step_y;
	float	floor_x;
	float	floor_y;
	int		cell_x;
	int		cell_y;
	int		tex_x;
	int		tex_y;
	int		tex_floor;
	int		tex_ceil;
	int		floor_color;
	int		ceil_color;
}	t_bkground;


typedef struct s_cube
{
	int				**map;
	t_parse			parse;
	t_elem			elem;
	t_player		player;
	t_raycast		raycast;
	t_bkground		bkground;
	t_frame			frame;
	t_sprite		sprite[NB_SPRITES];
	t_sprites		sprites;
	t_vars			vars;
	t_data			data;
	t_move			move;
	t_tex			tex;
	int				buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
	double			buffer_z[SCREEN_WIDTH];
}	t_cube;

/* --------------------------  PROTOTYPE GAME  --------------------------- */

// prototypes draw textures
void	calculate_texture(t_cube *cube);
void	fill_texture(t_cube *cube, int x);
void	draw_buffer(t_cube *cube);

// exit game
int		exit_game(t_cube *cube, int exit_status);

// prototypes generate textures
int		generate_textures(t_cube *cube);

// prototypes handle events
int		handle_keypress(int keycode, t_cube *cube);
int		handle_keyrelease(int keycode, t_cube *cube);

// prototypes move player
void	move_player(t_cube *cube);

// prototypes play game
void	play_game(t_cube *cube);

// prototypes raycast_walls
void	raycast_walls(t_cube *cube);

// prototypes raycast_floor_ceiling
void	raycast_floor_ceiling(t_cube *cube);

/* --------------------------  PROTOTYPE PARSING  --------------------------- */

// check the map is surrounded by wall
int		confirm_map(t_cube *cube, t_limits max, int y, int x);

// get file data and parse it
int		get_data(t_cube *cube, char *file);

// get data from the file which relate to element identifier and parse it
int		get_elem(t_cube *cube, int fd);

// get data from the file line by line
int		get_file_line(int fd, char **line);

// get data from the file which relate to the map and parse it
int		get_map(t_cube *cube, int fd);

//transform map form char to int
int		map_to_int(t_cube *cube);

// used to parse the map
int		is_valid_cell(char **map, int y, int x);
int		player_start(t_cube *cube, int y, int x);
void	define_limits(t_limits *max, char **map, int y);
int		confirm_map(t_cube *cube, t_limits max, int y, int x);

/* --------------------------  PROTOTYPE UTILS  --------------------------- */

// print simple error message
void	ft_error(char *str);

// free table splited
void	free_split(char **str);
void	free_cube(t_cube *cube);
void	free_tab_int(int **to_free);

// get time
double	get_time(void);

//init data to start game
int		init_game(t_cube *cube);

//init data for parsing
int		init_player(t_cube *cube, t_player define, double y, double x);
void	init_cube(t_cube *cube);

//map utils
int		rgb_format(char *str);
int		color_atoi(char *str, int *color);
int		remove_n(char **tmp);
int		file_type(char *str, char *type);
int		split_size(char **str);

// mlx utils

int		combine_rgb(int r, int g, int b);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

/* --------------------------  PROTOTYPE SPRITES  --------------------------- */

// calcul sprites
void	init_calc_sprites(t_cube *cube, int i);
void	calc_height_width(t_cube *cube, int i);
void	draw_pixels_sprites(t_cube *cube, int i);

// draw sprites
void	draw_sprites(t_cube *cube);

#endif
