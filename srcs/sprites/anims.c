/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anims.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 09:49:21 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/17 16:07:40 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	change_smoke_texture(t_cube *cube, t_obj *obj)
{
	if (obj->start_frame > obj->time_anim)
	{
		obj->texture++;
		obj->time_anim += TIME_ANIM;
	}
	if (obj->texture == 17)
	{
		obj->texture = 10;
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
		if (obj->texture >= 10 && obj->texture <= 16 && obj->draw)
			change_smoke_texture(cube, obj);
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

	obj = cube->obj;
	while (obj)
	{
		if (obj->texture >= 18 && obj->texture <= 26 && obj->draw)
		{
			if (!obj->dead)
				change_enemy_texture(cube, obj);
			else
			{
				obj->texture = 26;
				if (obj->start_frame > 2 * obj->time_anim)
					obj->draw = 0;
				obj->start_frame += cube->frame.frame_time;
			}
		}
		obj = obj->next;
	}
}
