/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:40:41 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/08 19:39:08 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	handle_keypress(int keycode, t_cube *cube)
{
	(void)cube;
	printf("keycode = %d\n", keycode);
	if (keycode == 119)
		game->move.up = 1;
	if (keycode == 115)
		game->move.down = 1;
	if (keycode == 97)
		game->move.left = 1;
	if (keycode == 100)
		game->move.right = 1;
	return (EXIT_SUCCESS);
}

int	handle_keyrelease(int keycode, t_cube *cube)
{
	if (keycode == 119)
		game->move.up = 0;
	if (keycode == 115)
		game->move.down = 0;
	if (keycode == 97)
		game->move.left = 0;
	if (keycode == 100)
		game->move.right = 0;
	return (EXIT_SUCCESS);
}
