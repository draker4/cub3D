/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:50:52 by bperriol          #+#    #+#             */
/*   Updated: 2023/02/06 20:48:53 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <sys/time.h>
# include <stdio.h>
double	get_time(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	printf("sec=%ld et micro=%f\n", tp.tv_sec, (double)tp.tv_usec / 1000000);
	return ((double)tp.tv_sec + (double)tp.tv_usec / 1000000);
}
