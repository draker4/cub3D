/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:40:41 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/17 15:35:11 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	handle_keypress(int keycode, t_cube *cube)
{
	if (keycode == W)
		cube->move.up = 1;
	if (keycode == S)
		cube->move.down = 1;
	if (keycode == A)
		cube->move.left = 1;
	if (keycode == D)
		cube->move.right = 1;
	if (keycode == RIGHT)
		cube->move.rotate_right = 1;
	if (keycode == LEFT)
		cube->move.rotate_left = 1;
	if (keycode == SPACE)
	{
		cube->weapon.start_frame = 0;
		cube->attack = 1;
	}
	if (keycode == ESCAPE)
		exit_game(cube, 0);
	return (EXIT_SUCCESS);
}

int	handle_keyrelease(int keycode, t_cube *cube)
{
	if (keycode == W)
		cube->move.up = 0;
	if (keycode == S)
		cube->move.down = 0;
	if (keycode == A)
		cube->move.left = 0;
	if (keycode == D)
		cube->move.right = 0;
	if (keycode == RIGHT)
		cube->move.rotate_right = 0;
	if (keycode == LEFT)
		cube->move.rotate_left = 0;
	return (EXIT_SUCCESS);
}

int	handle_mouse(int x, int y, t_cube *cube)
{
	static int	prev;
	int			current;

	current = x;
	if (current < prev)
		rotate_player(cube, cube->player.dir_x, cube->player.plane_x,
			MOUSE_LEFT);
	else if (current > prev)
		rotate_player(cube, cube->player.dir_x, cube->player.plane_x,
			MOUSE_RIGHT);
	prev = current;
	return (y);
}
