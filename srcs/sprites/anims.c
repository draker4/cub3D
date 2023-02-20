/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anims.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 09:49:21 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/20 11:57:14 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	change_texture(t_cube *cube, t_obj *obj, int begin, int end)
{
	if (obj->start_frame > obj->time_anim)
	{
		obj->texture++;
		obj->time_anim += TIME_ANIM;
	}
	if (obj->texture == end + 1)
	{
		obj->texture = begin;
		obj->start_frame = 0;
		obj->time_anim = TIME_ANIM;
	}
	obj->start_frame += cube->frame.frame_time;
}

void	anim_smoke(t_cube *cube)
{
	t_obj	*obj;

	obj = cube->obj;
	while (obj)
	{
		if (obj->texture >= 10 && obj->texture <= 16)
			change_texture(cube, obj, 10, 16);
		else if (obj->texture >= 27 && obj->texture <= 36)
			change_texture(cube, obj, 10, 36);
		obj = obj->next;
	}
}

static void	change_enemy_texture(t_cube *cube, t_obj *obj)
{
	if (obj->start_frame > obj->time_anim)
	{
		obj->texture++;
		obj->time_anim += TIME_ANIM;
	}
	if (obj->texture == 26)
	{
		obj->texture = 18;
		obj->start_frame = 0;
		obj->time_anim = TIME_ANIM;
	}
	obj->start_frame += cube->frame.frame_time;
}

void	anim_enemy(t_cube *cube)
{
	t_obj	*obj;
	t_obj	*next;

	obj = cube->obj;
	while (obj)
	{
		next = obj->next;
		if (obj->texture >= 18 && obj->texture <= 26)
		{
			if (!obj->dead)
				change_enemy_texture(cube, obj);
			else
			{
				obj->texture = 26;
				obj->start_frame += cube->frame.frame_time;
			}
			if (obj->dead && obj->start_frame > 2 * obj->time_anim)
			{
				del_one(&cube->obj, obj);
				cube->nb_objs = obj_size(cube->obj);
			}
		}
		obj = next;
	}
}
