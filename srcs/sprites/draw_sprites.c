/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:15:51 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/15 18:17:37 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	calculate_distance(t_cube *cube)
{
	t_obj	*current;

	current = cube->obj;
	while (current)
	{
		current->distance = \
		((cube->player.pos_x - current->pos_x) * \
		(cube->player.pos_x - current->pos_x)) + \
		((cube->player.pos_y - current->pos_y) * \
		(cube->player.pos_y - current->pos_y));
		current = current->next;
	}
}

static void	sort_current(t_obj **current, t_obj **prev_current, t_cube *cube)
{
	t_obj	*current_next;
	t_obj	*tmp;
	t_obj	*prev_tmp;

	tmp = (*current)->next;
	prev_tmp = *current;
	while (tmp)
	{
		if (tmp->distance > (*current)->distance)
		{
			prev_tmp->next = *current;
			current_next = (*current)->next;
			(*current)->next = tmp->next;
			if (!(*prev_current))
				cube->obj = tmp;
			else
				(*prev_current)->next = tmp;
			tmp->next = current_next;
		}
		tmp = tmp->next;
	}
}

static void	sort_sprites(t_cube *cube)
{
	t_obj	*current;
	t_obj	*prev_current;

	if (cube->nb_objs == 1)
		return ;
	current = cube->obj;
	prev_current = NULL;
	while (current)
	{
		sort_current(&current, &prev_current, cube);
		prev_current = current;
		current = current->next;
	}
}

void	draw_sprites(t_cube *cube)
{
	t_obj	*current;

	current = cube->obj;
	calculate_distance(cube);
	sort_sprites(cube);
	while (current)
	{
		init_calc_sprites(cube, current);
		calc_height_width(cube, current);
		draw_pixels_sprites(cube, current);
		current = current->next;
	}
}
