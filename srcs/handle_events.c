/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:40:41 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/09 11:36:52 by bperriol         ###   ########lyon.fr   */
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
	return (EXIT_SUCCESS);
}
