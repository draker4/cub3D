/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:01:06 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/17 11:54:49 by bperriol         ###   ########lyon.fr   */
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

# define SCREEN_TITLE "****CUB3D BAPT'S TEAM****"
# define SCREEN_WIDTH 2000
# define SCREEN_HEIGHT 1000
# define TEX_WIDTH 256
# define TEX_HEIGHT 256
# define MOVE_SPEED 4.0
# define ROT_SPEED 2.0
# define WALL_HEIGHT 1.5
# define ANGLE 0.66
# define NB_TEXTURES 18
# define NB_SP_WEAPON 7
# define NB_BOOM 6
# define MAP_SIZE 200
# define MAP_POS 10

# define BLACK 0x000000
# define BLUE 0x0000FF
# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define PINK 0xFF00FF
# define YELLOW 0xFFF000
# define AZUL 0x00FFFF
# define GREEN 0x00FF00

# define W 119
# define S 115
# define A 97
# define D 100
# define F 102
# define SPACE 32
# define RIGHT 65363
# define LEFT 65361
# define ESCAPE 65307
# define MOUSE_LEFT 1
# define MOUSE_RIGHT 2

# define E_ARG_NB "Select one map only\n"
# define E_CELL "Forbidden cell type used\n"
# define E_ELEM "The data elements have to be check\n"
# define E_FILE_TYPE "The map should be of type .cub\n"
# define E_PLAYER "Player starting position define more than once\n"
# define E_NO_START "No starting position defined\n"
# define E_WALL "The map isn't closed or there is an empty field as a floor \
cell\n"
# define E_DOOR "A door is not set properly\n"
# define E_XPM_IMAGE "Mlx_xpm_file_to_image function error\n"
# define E_MLX_WINDOW "Mlx_new_window function error\n"

# define LIGHT_PATH "./sprites/greenlight.xpm"
# define BARREL_PATH "./sprites/barrel.xpm"
# define PILLAR_PATH "./sprites/pillar.xpm"
# define PUNCH1_PATH "./sprites/punch1.xpm"
# define PUNCH2_PATH "./sprites/punch2.xpm"
# define PUNCH3_PATH "./sprites/punch3.xpm"
# define DOOR_PATH "./sprites/door.xpm"
# define BOOM1_PATH "./sprites/boom1.xpm"
# define BOOM2_PATH "./sprites/boom2.xpm"
# define BOOM3_PATH "./sprites/boom3.xpm"
# define BOOM4_PATH "./sprites/boom4.xpm"
# define BOOM5_PATH "./sprites/boom5.xpm"
# define BOOM6_PATH "./sprites/boom6.xpm"
# define BOOM7_PATH "./sprites/boom7.xpm"
# define BOOM8_PATH "./sprites/boom8.xpm"
# define BOOM9_PATH "./sprites/boom9.xpm"
# define BOOM10_PATH "./sprites/boom10.xpm"
# define SMOKE1_PATH "./sprites/smoke1.xpm"
# define SMOKE2_PATH "./sprites/smoke2.xpm"
# define SMOKE3_PATH "./sprites/smoke3.xpm"
# define SMOKE4_PATH "./sprites/smoke4.xpm"
# define SMOKE5_PATH "./sprites/smoke5.xpm"
# define SMOKE6_PATH "./sprites/smoke6.xpm"
# define SMOKE7_PATH "./sprites/smoke7.xpm"
# define GUN1_PATH "./sprites/gun1.xpm"
# define GUN2_PATH "./sprites/gun2.xpm"
# define GUN3_PATH "./sprites/gun3.xpm"
# define GUN4_PATH "./sprites/gun4.xpm"
# define GUN_COLLECT "./sprites/gun_collect.xpm"

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

typedef struct s_obj
{
	double			pos_x;
	double			pos_y;
	int				texture;
	double			distance;
	double			u_div;
	double			v_div;
	double			v_move;
	int				draw;
	double			start_frame;
	struct s_obj	*next;
}	t_obj;

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
	int		door;
	int		open_door;
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
	int		floor_color;
	int		ceil_color;
}	t_bkground;

typedef struct s_weapon
{
	int		**tex;
	int		gun;
	int		nb_frame;
	double	start_frame;
}	t_weapon;

typedef struct s_boom
{
	int		**tex;
	int		nb_frame;
	double	start_frame;
	int		boom;
}	t_boom;

typedef struct s_cube
{
	int				**map;
	t_parse			parse;
	t_elem			elem;
	t_player		player;
	t_raycast		raycast;
	t_bkground		bkground;
	t_frame			frame;
	t_obj			*obj;
	t_sprites		sprites;
	t_vars			vars;
	t_data			data;
	t_move			move;
	t_tex			tex;
	t_weapon		weapon;
	t_limits		limits;
	t_boom			boom;
	int				nb_objs;
	int				attack;
	int				buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
	double			buffer_z[SCREEN_WIDTH];
}	t_cube;

/* --------------------------  PROTOTYPE GAME  --------------------------- */

// collisions sprites
void	move_sprites_front(t_cube *cube);
void	move_sprites_side(t_cube *cube);

// create minimap
void	draw_map(t_cube *cube);

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
int		handle_mouse(int x, int y, t_cube *cube);

// prototypes move player
void	rotate_player(t_cube *cube, double prev_dir_x, double prev_plane_x,
			int mouse);
void	move_player(t_cube *cube);

// open door
void	open_close_door(t_cube *cube);

// prototypes play game
void	play_game(t_cube *cube);

// prototypes raycast_walls
void	raycast_walls(t_cube *cube);

// prototypes raycast_floor_ceiling
void	raycast_floor_ceiling(t_cube *cube);

/* --------------------------  PROTOTYPE PARSING  --------------------------- */

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
int		player_start(t_cube *cube, int y, int x);
void	define_limits(t_limits *max, char **map, int y);
int		parse_cell(t_cube *cube, int y, int x);

// analyse obj and prepare list of object to be used
int		parse_obj(t_cube *cube, int y, int x);

/* --------------------------  PROTOTYPE UTILS  --------------------------- */

// print simple error message
void	ft_error(char *str);

// free table splited
void	free_split(char **str);
void	free_cube(t_cube *cube);
void	free_tab_int(int **to_free);

// get time
double	get_time(void);

// init data to start game
int		init_game(t_cube *cube);

// init data for parsing
int		init_player(t_cube *cube, t_player define, int y, int x);
void	init_cube(t_cube *cube);

// manage obj list
t_obj	*new_obj(t_obj data, t_cube *cube, char cell);
void	free_obj(t_obj **obj);
void	obj_add_back(t_obj **obj, t_obj *new);
int		obj_size(t_obj *obj);
void	change_obj_state(t_cube *cube, double x, double y, int state);

// map utils
int		rgb_format(char *str);
int		color_atoi(char *str, int *color);
int		remove_n(char **tmp);
int		file_type(char *str, char *type);
int		split_size(char **str);

// mlx utils
int		combine_rgb(int r, int g, int b);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	fill_pixel(t_cube *cube, int index, int color);

/* --------------------------  PROTOTYPE SPRITES  --------------------------- */

// anim smoke
void	anim_smoke(t_cube *cube);

// calcul sprites
void	init_calc_sprites(t_cube *cube, t_obj *current);
void	calc_height_width(t_cube *cube, t_obj *current);
void	draw_pixels_sprites(t_cube *cube, t_obj *current);

// draw boom
void	draw_boom(t_cube *cube);

// draw sprites
void	draw_sprites(t_cube *cube);

// draw weapon
void	draw_weapon(t_cube *cube);

#endif
