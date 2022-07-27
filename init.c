/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabasset <mabasset@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:41:43 by mabasset          #+#    #+#             */
/*   Updated: 2022/07/27 21:10:18 by mabasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_init_p(t_cub3D *data, char c)
{
	if (c == 'N')
		data->p.angle = 3 * PI / 2;
	else if (c == 'S')
		data->p.angle = PI / 2;
	else if (c == 'E')
		data->p.angle = 0;
	else if (c == 'W')
		data->p.angle = PI;
}

void	ft_find_p(t_cub3D *data)
{
	int		row;
	int		col;
	char	c;

	row = 0;
	while (data->map[row] != NULL)
	{
		col = 0;
		while (data->map[row][col] != '\0')
		{
			c = data->map[row][col];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				ft_init_p(data, c);
				data->p.x = col + 0.5;
				data->p.y = row + 0.5;
			}
			col++;
		}
		row++;
	}
}

void	ft_init_img(t_cub3D *data)
{
	int		y;
	int		x;
	int		w;
	int		h;

	data->img.img = mlx_new_image(data->mlx, data->s_w, data->s_h);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp, &data->img.ll, &data->img.e);
	y = 0;
	while (y < data->s_h)
	{
		x = 0;
		while (x < data->s_w)
		{
			my_mlx_pixel_put(data, x, y, WP);
			x++;
		}
		y++;
	}
	data->gun = mlx_xpm_file_to_image(data->mlx, GUN, &w, &h);
}

void	ft_init(t_cub3D *data)
{
	float	la;

	ft_find_p(data);
	data->p.dx = cos(data->p.angle);
	data->p.dy = sin(data->p.angle);
	data->p.w = 0;
	data->p.s = 0;
	data->p.a = 0;
	data->p.d = 0;
	data->p.left = 0;
	data->p.right = 0;
	ft_init_img(data);
}