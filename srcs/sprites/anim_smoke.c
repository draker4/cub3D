/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_smoke.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 09:49:21 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/17 10:25:56 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	change_smoke_texture(t_cube *cube, t_obj *obj)
{
	static double	time;

	if (obj->texture == 16)
	{
		obj->texture = 10;
		obj->start_frame = 0;
		time = 0;
	}
	if (obj->start_frame > time)
	{
		obj->texture++;
		time += 0.1;
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
