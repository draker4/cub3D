/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:40:41 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/13 14:50:46 by bboisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	handle_keypress(int keycode, t_cube *cube)
{
	if (keycode == 119)
		cube->move.up = 1;
	if (keycode == 115)
		cube->move.down = 1;
	if (keycode == 97)
		cube->move.left = 1;
	if (keycode == 100)
		cube->move.right = 1;
	if (keycode == 65363)
		cube->move.rotate_right = 1;
	if (keycode == 65361)
		cube->move.rotate_left = 1;
	if (keycode == 65307)
		exit_game(cube);
	return (EXIT_SUCCESS);
}

int	handle_keyrelease(int keycode, t_cube *cube)
{
	if (keycode == 119)
		cube->move.up = 0;
	if (keycode == 115)
		cube->move.down = 0;
	if (keycode == 97)
		cube->move.left = 0;
	if (keycode == 100)
		cube->move.right = 0;
	if (keycode == 65363)
		cube->move.rotate_right = 0;
	if (keycode == 65361)
		cube->move.rotate_left = 0;
	return (EXIT_SUCCESS);
}
