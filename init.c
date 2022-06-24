/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabasset <mabasset@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:41:43 by mabasset          #+#    #+#             */
/*   Updated: 2022/06/24 14:48:51 by mabasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_init_img(t_cub3D *data)
{
	int		w;
	int		h;

	data->img.p = mlx_xpm_file_to_image(data->mlx, PLAYER, &w, &h);
	data->img.w = mlx_xpm_file_to_image(data->mlx, WALL, &w, &h);
	data->img.f = mlx_xpm_file_to_image(data->mlx, FLOOR, &w, &h);
}

void	ft_init(t_cub3D *data)
{
	data->p.x = 350;
	data->p.y = 750;
	data->p.a = 0;
	data->p.dx = cos(data->p.a);
	data->p.dy = sin(data->p.a);
	ft_init_img(data);
}