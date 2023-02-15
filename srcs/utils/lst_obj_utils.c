/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_obj_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 04:56:37 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/15 15:59:02 by bboisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_obj	*new_obj(t_obj data, int y, int x)
{
	t_obj	*new;

	new = malloc(sizeof(t_obj));
	if (!new)
		return (perror("new_obj - malloc"), NULL);
	new->pos_x = (double)x + 0.5;
	new->pos_y = (double)y + 0.5;
	new->texture = data.texture;
	new->distance = data.distance;
	new->u_div = data.u_div;
	new->v_div = data.v_div;
	new->v_move = data.v_move;
	new->next = NULL;
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
