/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_enemy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:15:15 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/20 14:13:57 by bboisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	follow(t_cube *cube, t_obj *obj, double speed, int type)
{
	if (cube->map[(int)obj->pos_y][(int)(obj->pos_x + \
	(cube->player.pos_x - obj->pos_x) * speed)] == type)
		obj->pos_x += (cube->player.pos_x - obj->pos_x) * speed;
	if (cube->map[(int)(obj->pos_y + (cube->player.pos_y - obj->pos_y) * \
	speed)][(int)(obj->pos_x)] == type)
		obj->pos_y += (cube->player.pos_y - obj->pos_y) * speed;
}

static void	move(t_cube *cube, t_obj *obj, double speed, int type)
{
	if (obj->vertical)
	{
		if (cube->map[(int)(obj->pos_y + speed * obj->dir)] \
		[(int)obj->pos_x] == type)
			obj->pos_y += speed * obj->dir;
		else if (cube->map[(int)(obj->pos_y + speed * obj->dir)] \
		[(int)obj->pos_x] == 1 || cube->map[(int)(obj->pos_y + \
		speed * obj->dir)][(int)obj->pos_x] == 2 || cube->map[(int) \
		(obj->pos_y + speed * obj->dir)][(int)obj->pos_x] == 3)
			obj->dir *= -1;
	}
	else
	{
		if (cube->map[(int)obj->pos_y] \
		[(int)(obj->pos_x + speed * obj->dir)] == type)
			obj->pos_x += speed * obj->dir;
		else if (cube->map[(int)obj->pos_y] \
		[(int)(obj->pos_x + speed * obj->dir)] == 1 || cube->map[(int) \
		obj->pos_y][(int)(obj->pos_x + speed * obj->dir)] == 2 || \
		cube->map[(int)obj->pos_y][(int)(obj->pos_x + speed * obj->dir)] == 3)
			obj->dir *= -1;
	}
}

static void	choose_move(t_cube *cube, t_obj *obj)
{
	if (pow(obj->pos_x - cube->player.pos_x, 2) + \
	pow(obj->pos_y - cube->player.pos_y, 2) < ENEMY_DIST_FOLLOW)
	{
		follow(cube, obj, SPEED_ENEMY * cube->frame.frame_time, 0);
		follow(cube, obj, SPEED_ENEMY * cube->frame.frame_time, 4);
	}
	else
	{
		move(cube, obj, SPEED_ENEMY * cube->frame.frame_time, 0);
		move(cube, obj, SPEED_ENEMY * cube->frame.frame_time, 4);
	}
	if (pow(obj->pos_x - cube->player.pos_x, 2) + \
	pow(obj->pos_y - cube->player.pos_y, 2) < ENEMY_DIST_DEAD)
	{
		if (write(1, "Oh no! You died!\n", 17))
			exit_game(cube, 1);
	}
}

void	move_enemy(t_cube *cube)
{
	t_obj	*obj;

	obj = cube->obj;
	while (obj)
	{
		if (obj->texture >= 18 && obj->texture <= 25 && !obj->dead)
			choose_move(cube, obj);
		obj = obj->next;
	}
}
