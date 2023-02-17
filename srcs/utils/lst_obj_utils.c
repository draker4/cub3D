/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_obj_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 04:56:37 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/17 11:29:11 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_obj	*new_obj(t_obj data, t_cube *cube, char cell)
{
	t_obj	*new;

	new = malloc(sizeof(t_obj));
	if (!new)
		return (perror("new_obj - malloc"), NULL);
	new->pos_x = data.pos_x;
	new->pos_y = data.pos_y;
	new->texture = data.texture;
	new->distance = data.distance;
	new->u_div = data.u_div;
	new->v_div = data.v_div;
	new->v_move = data.v_move;
	new->draw = data.draw;
	new->start_frame = data.start_frame;
	new->next = NULL;
	cube->parse.map[(int)data.pos_y][(int)data.pos_x] = cell;
	return (new);
}

void	free_obj(t_obj **obj)
{
	t_obj	*clear;
	t_obj	*tmp;

	if (!obj)
		return ;
	clear = *obj;
	while (clear)
	{
		tmp = clear;
		clear = clear->next;
		free(tmp);
	}
	*obj = NULL;
}

void	obj_add_back(t_obj **obj, t_obj *new)
{
	t_obj	*current;

	if (obj && *obj)
	{
		current = *obj;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	else if (obj)
		*obj = new;
}

int	obj_size(t_obj *obj)
{
	int	i;

	i = 0;
	if (!obj)
		return (0);
	while (obj)
	{
		i++;
		obj = obj->next;
	}
	return (i);
}

void	change_obj_state(t_cube *cube, double x, double y, int state)
{
	t_obj	*obj;

	obj = cube->obj;
	while (obj)
	{
		if (obj->pos_x == x && obj->pos_y == y)
			break ;
		obj = obj->next;
	}
	if (!obj)
		return ;
	obj->draw = state;
	obj->start_frame = 0;
}
