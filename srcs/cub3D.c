/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:22:39 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/14 17:07:46 by bboisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_cube	cube;

	if (argc != 2)
		return (ft_error(E_ARG_NB), EXIT_FAILURE);
	if (file_type(argv[1], ".cub"))
		return (ft_error(E_FILE_TYPE), EXIT_FAILURE);
	if (get_data(&cube, argv[1]))
		return (free_cube(&cube), EXIT_FAILURE);
	if (init_game(&cube))
		return (free_cube(&cube), EXIT_FAILURE);
	play_game(&cube);
	return (EXIT_SUCCESS);
}
