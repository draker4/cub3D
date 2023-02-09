/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:43:42 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/09 15:37:07 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_camera(t_cube *cube, int x)
{
	cube->raycast.camera_x = (2 * x / (double) SCREEN_WIDTH) - 1;
	cube->raycast.ray_dir_x = cube->player.dir_x + cube->player.plane_x * \
	cube->raycast.camera_x;
	cube->raycast.ray_dir_y = cube->player.dir_y + cube->player.plane_y * \
	cube->raycast.camera_x;
	cube->raycast.map_x = (int) cube->player.pos_x;
	cube->raycast.map_y = (int) cube->player.pos_y;
	if (!cube->raycast.ray_dir_x)
		cube->raycast.delta_dist_x = 1e30;
	else
		cube->raycast.delta_dist_x = fabs(1 / cube->raycast.ray_dir_x);
	if (!cube->raycast.ray_dir_y)
		cube->raycast.delta_dist_y = 1e30;
	else
		cube->raycast.delta_dist_y = fabs(1 / cube->raycast.ray_dir_y);
	cube->raycast.hit = 0;
}

static void	init_dir(t_cube *cube)
{
	if (cube->raycast.ray_dir_x < 0)
	{
		cube->raycast.step_x = -1;
		cube->raycast.side_dist_x = (cube->player.pos_x - \
		cube->raycast.map_x) * cube->raycast.delta_dist_x;
	}
	else
	{
		cube->raycast.step_x = 1;
		cube->raycast.side_dist_x = (cube->raycast.map_x + 1.0 - \
		cube->player.pos_x) * cube->raycast.delta_dist_x;
	}
	if (cube->raycast.ray_dir_y < 0)
	{
		cube->raycast.step_y = -1;
		cube->raycast.side_dist_y = (cube->player.pos_y - \
		cube->raycast.map_y) * cube->raycast.delta_dist_y;
	}
	else
	{
		cube->raycast.step_y = 1;
		cube->raycast.side_dist_y = (cube->raycast.map_y + 1.0 - \
		cube->player.pos_y) * cube->raycast.delta_dist_y;
	}
}

static void	dda_algo(t_cube *cube)
{
	while (!cube->raycast.hit)
	{
		if (cube->raycast.side_dist_x < cube->raycast.side_dist_y)
		{
			cube->raycast.side_dist_x += cube->raycast.delta_dist_x;
			cube->raycast.map_x += cube->raycast.step_x;
			cube->raycast.side = 0;
		}
		else
		{
			cube->raycast.side_dist_y += cube->raycast.delta_dist_y;
			cube->raycast.map_y += cube->raycast.step_y;
			cube->raycast.side = 1;
		}
		if (cube->map[cube->raycast.map_x][cube->raycast.map_y])
			cube->raycast.hit = 1;
	}
}

static void	draw_line_wall(t_cube *cube)
{
	if (!cube->raycast.side)
		cube->raycast.dist_plan_wall = \
		(cube->raycast.side_dist_x - cube->raycast.delta_dist_x);
	else
		cube->raycast.dist_plan_wall = \
		(cube->raycast.side_dist_y - cube->raycast.delta_dist_y);
	cube->raycast.line_height = \
	(int)(SCREEN_HEIGHT / cube->raycast.dist_plan_wall);
	cube->raycast.line_start = \
	-cube->raycast.line_height / 2 + SCREEN_HEIGHT / 2;
	if (cube->raycast.line_start < 0)
		cube->raycast.line_start = 0;
	cube->raycast.line_end = \
	cube->raycast.line_height / 2 + SCREEN_HEIGHT / 2;
	if (cube->raycast.line_end >= SCREEN_HEIGHT)
		cube->raycast.line_end = SCREEN_HEIGHT - 1;
}

void	raycasting(t_cube *cube)
{
	int	x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		init_camera(cube, x);
		init_dir(cube);
		dda_algo(cube);
		draw_line_wall(cube);
		
		  //choose wall color
     	 switch(cube->map[cube->raycast.map_x][cube->raycast.map_y])
      	{
        case 1:  cube->raycast.color = create_trgb(1, 255, 160, 122);    break; //red
        case 2:  cube->raycast.color = create_trgb(1, 127, 255, 0);  break; //green
        case 3:  cube->raycast.color = create_trgb(1, 175, 238, 238);   break; //blue
        case 4:  cube->raycast.color = create_trgb(1, 255, 250, 250);  break; //white
        default: cube->raycast.color = create_trgb(1, 255, 228, 181); break; //yellow
     	}
		if (cube->raycast.side == 1)
			cube->raycast.color = cube->raycast.color / 2;
		draw_line(cube, x);
		x++;
	}
}
