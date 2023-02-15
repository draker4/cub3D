/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:15:51 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/15 19:13:07 by bboisson         ###   ########.fr       */
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

static void	swap_obj(t_obj **current, t_obj **check, t_obj tmp)
{
	(*current)->pos_x = (*check)->pos_x;
	(*current)->pos_y = (*check)->pos_y;
	(*current)->texture = (*check)->texture;
	(*current)->distance = (*check)->distance;
	(*current)->u_div = (*check)->u_div;
	(*current)->v_div = (*check)->v_div;
	(*current)->v_move = (*check)->v_move;
	(*check)->pos_x = tmp.pos_x;
	(*check)->pos_y = tmp.pos_y;
	(*check)->texture = tmp.texture;
	(*check)->distance = tmp.distance;
	(*check)->u_div = tmp.u_div;
	(*check)->v_div = tmp.v_div;
	(*check)->v_move = tmp.v_move;
}

static void	sort_sprites(t_cube *cube)
{
	int		i;
	int		j;
	t_obj	*current;
	t_obj	*check;

	i = -1;
	current = cube->obj;
	while (++i < cube->nb_objs)
	{
		j = i;
		check = current->next;
		while (++j < cube->nb_objs)
		{
			if (check->distance > current->distance)
				swap_obj(&current, &check, *current);
			check = check->next;
		}
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
