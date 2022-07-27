/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabasset <mabasset@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 14:19:53 by mabasset          #+#    #+#             */
/*   Updated: 2022/07/27 14:24:06 by mabasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_mlx_pixel_put(t_cub3D *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img.addr + (y * data->img.ll + x * (data->img.bpp / 8));
	*(unsigned int *)dst = color;
}
