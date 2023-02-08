/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:50:52 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/08 15:56:17 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	get_time(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return ((double)tp.tv_sec + (double)tp.tv_usec / 1000000);
}
