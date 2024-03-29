/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_enemy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:33:50 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/20 14:10:59 by bboisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	punch_enemy(t_cube *cube, t_obj *obj)
{
	if (pow(cube->player.pos_x + cube->player.dir_x - obj->pos_x, 2) \
		+ pow(cube->player.pos_y + cube->player.dir_y - obj->pos_y, 2) \
		< DETECT_ENEMY)
	{
		obj->dead = 1;
		obj->start_frame = 0;
	}
}

static void	shoot_enemy(t_cube *cube, t_obj *obj)
{
	int	i;

	i = 1;
	while (cube->map[(int)(cube->player.pos_y + i * cube->player.dir_y)] \
	[(int)(cube->player.pos_x + i * cube->player.dir_x)] != 1)
	{
		if (pow(cube->player.pos_x + i * cube->player.dir_x - obj->pos_x, 2) \
		+ pow(cube->player.pos_y + i * cube->player.dir_y - obj->pos_y, 2) \
		< DETECT_ENEMY)
		{
			obj->dead = 1;
			cube->kill = 1;
			obj->start_frame = 0;
			return ;
		}
		i++;
	}
}

void	kill_enemy(t_cube *cube)
{
	t_obj	*obj;

	obj = cube->obj;
	while (obj)
	{
		if (obj->texture >= 18 && obj->texture <= 25 && !obj->dead)
		{
			if (cube->weapon.gun)
				shoot_enemy(cube, obj);
			else
				punch_enemy(cube, obj);
		}
		obj = obj->next;
	}
}
