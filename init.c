/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabasset <mabasset@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:41:43 by mabasset          #+#    #+#             */
/*   Updated: 2022/09/22 20:31:06 by mabasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_init_info(t_cub3D *data)
{
	data->NO = NULL;
	data->SO = NULL;
	data->WE = NULL;
	data->EA = NULL;
	data->F = -1;
	data->C = -1;
}

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

	data->img.img = mlx_new_image(data->mlx, data->s_w, data->s_h);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp, &data->img.ll, &data->img.e);
	y = 0;
	while (y < data->s_h)
	{
		x = 0;
		while (x < data->s_w)
		{
			if (!((x > data->s_w / 2 - FOV * 8 && x < data->s_w / 2 + FOV * 8) && (y > data->s_h / 2 - FOV * 4 && y < data->s_h / 2 + FOV * 4)))
				my_mlx_pixel_put(data, x, y, WP);
			x++;
		}
		y++;
	}
}

void	ft_init_sprites(t_cub3D *data)
{
	int		w;
	int		h;

	data->s.gun1 = mlx_xpm_file_to_image(data->mlx, GUN, &w, &h);
	data->s.gun2 = mlx_xpm_file_to_image(data->mlx, GUN2, &w, &h);
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
	data->frame = 0;
	ft_init_img(data);
	ft_init_sprites(data);
	data->text[0].img = mlx_xpm_file_to_image(data->mlx, data->NO, &data->text[0].w, &data->text[0].h);
	data->text[0].addr = mlx_get_data_addr(data->text[0].img, &data->text[0].bpp, &data->text[0].ll, &data->text[0].e);
	data->text[1].img = mlx_xpm_file_to_image(data->mlx, data->SO, &data->text[1].w, &data->text[1].h);
	data->text[1].addr = mlx_get_data_addr(data->text[1].img, &data->text[1].bpp, &data->text[1].ll, &data->text[1].e);
	data->text[2].img = mlx_xpm_file_to_image(data->mlx, data->WE, &data->text[2].w, &data->text[2].h);
	data->text[2].addr = mlx_get_data_addr(data->text[2].img, &data->text[2].bpp, &data->text[2].ll, &data->text[2].e);
	data->text[3].img = mlx_xpm_file_to_image(data->mlx, data->EA, &data->text[3].w, &data->text[3].h);
	data->text[3].addr = mlx_get_data_addr(data->text[3].img, &data->text[3].bpp, &data->text[3].ll, &data->text[3].e);
	// printf("%p\n", data->text[0].addr);
	// printf("%p\n", data->text[1].addr);
}