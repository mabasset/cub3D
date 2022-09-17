/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabasset <mabasset@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:48:39 by mabasset          #+#    #+#             */
/*   Updated: 2022/09/17 18:15:35 by mabasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// void	ft_draw_frame(t_cub3D *data)
// {
// 	int	row;
// 	int	col;

// 	row = (data->s_h / 2) + FOV * 4 + 10;
// 	while (row < (data->s_h / 2 + FOV * 4) + FOV * 2)
// 	{
// 		col = data->s_w / 2 - FOV * 8;
// 		while (col < data->s_w / 2 + FOV * 8)
// 		{
// 			my_mlx_pixel_put(data, col, row, 139);
// 			col++;
// 		}
// 		row++;
// 	}
// }

// void	ft_draw_bar(t_cub3D *data)
// {
// 	ft_draw_frame(data);
// }

void	text_pixel_put(t_cub3D *data, int x, int y, t_text *text, int i)
{
	char	*dst;
	char	*src;
	int		color;

	dst = data->img.addr + (y * data->img.ll + x * (data->img.bpp / 8));
	if (text == NULL)
		*(unsigned int *)dst = BLACK;
	else
	{
		src = text->addr + ((int)data->hit_y[i] * text->ll + (int)data->hit_x[i] * (text->bpp / 8));
		data->hit_y[i] += 32 / (FOV * 4 / data->dist[i]);
		color = *(unsigned int *)src;
		*(unsigned int *)dst = color;
	}
}

void	text_pixel_put2(t_cub3D *data, int x, int y, t_text *text, int i)
{
	char	*dst;
	char	*src;
	int		color;

	dst = data->img.addr + (y * data->img.ll + x * (data->img.bpp / 8));
	if (text == NULL)
		*(unsigned int *)dst = BLACK;
	else
	{
		src = text->addr + ((int)data->hit_y[i] * text->ll + (int)data->hit_x[i] * (text->bpp / 8));
		data->hit_y[i] += 32 / (FOV * 4 / data->dist[i]);
		color = *(unsigned int *)src;
		*(unsigned int *)dst = color;
	}
}

void	ft_draw_col(t_cub3D *data, float dist, int x, t_text *text)
{
	int	i;

	if (dist < 1)
		dist = 1;
	i = 0;
	while (i < FOV * 4 - FOV * 4 / dist)
	{
		my_mlx_pixel_put(data, data->s_w / 2 - FOV * 8 + x, (data->s_h / 2) - FOV * 4 + i, data->C);
		i++;
	}
	while (i < (FOV * 4) + FOV * 4 / dist)
	{
		//my_mlx_pixel_put(data, data->s_w / 2 - FOV * 8 + x, (data->s_h / 2) - FOV * 4 + i, RED);
		text_pixel_put(data, data->s_w / 2 - FOV * 8 + x, (data->s_h / 2) - FOV * 4 + i, text, x);
		i++;
	}
	while (i < FOV * 8)
	{
		my_mlx_pixel_put(data, data->s_w / 2 - FOV * 8 + x, (data->s_h / 2) - FOV * 4 + i, data->F);
		i++;
	}
}

void	ft_draw_walls(t_cub3D *data)
{
	int	i;

	i = 0;
	while (i < FOV * 16)
	{
		if (data->orientation[i] == 1)
			ft_draw_col(data, data->dist[i], i, &data->text[0]);
		else if (data->orientation[i] == 2)
			ft_draw_col(data, data->dist[i], i, &data->text[1]);
		else if (data->orientation[i] == 3)
			ft_draw_col(data, data->dist[i], i, &data->text[2]);
		else if (data->orientation[i] == 4)
			ft_draw_col(data, data->dist[i], i, &data->text[3]);
		else
			ft_draw_col(data, data->dist[i], i, NULL);
		i++;
	}
}

int		ft_orientation(t_cub3D *data, float ra, float dist)
{
	float	dy;
	float	dx;

	dx = cos(ra);
	dy = sin(ra);
	dist -= 0.01;
	if (data->map[(int) (data->p.y + dy * dist - 0.01)][(int) (data->p.x + dx * dist)] == '1')
		return(1);
	else if (data->map[(int) (data->p.y + dy * dist + 0.01)][(int) (data->p.x + dx * dist)] == '1')
		return(2);
	else if (data->map[(int) (data->p.y + dy * dist)][(int) (data->p.x + dx * dist - 0.01)] == '1')
		return(3);
	else if (data->map[(int) (data->p.y + dy * dist)][(int) (data->p.x + dx * dist + 0.01)] == '1')
		return(4);
	return (5);
}

float	ft_ray_length(t_cub3D *data, float ra, int r)
{
	float	i;
	float	dx;
	float	dy;
	float	ca;

	dx = cos(ra);
	dy = sin(ra);
	i = 0;
	while (data->map[(int) (data->p.y + dy * i)][(int) (data->p.x + dx * i)] != '1')
		i += 0.01;
	data->orientation[r] = ft_orientation(data, ra, i);
	if (data->orientation[r] == 1)
		data->hit_x[r] = floor(((data->p.x + dx * i) - floor(data->p.x + dx * i)) * 64);
	else if (data->orientation[r] == 2)
		data->hit_x[r] = 64 - floor(((data->p.x + dx * i) - floor(data->p.x + dx * i)) * 64);
	else if (data->orientation[r] == 3)
		data->hit_x[r] = 64 - floor(((data->p.y + dy * i) - floor(data->p.y + dy * i)) * 64);
	else
		data->hit_x[r] = floor(((data->p.y + dy * i) - floor(data->p.y + dy * i)) * 64);
	data->hit_y[r] = 0;
	ca = data->p.angle - ra;
	ft_check_angle(&ca);
	i *= cos(ca);
	// if (i < 1)
	// 	data->hit_y[r] += floor(64 - floor(64 * i));
	return (i);
}

void	ft_raycast(t_cub3D *data)
{
	float	ra;
	int		r;

	ra = data->p.angle - FOV / 2 * RAD;
	ft_check_angle(&ra);
	r = 0;
	while (r < FOV * 16)
	{
		data->dist[r] = ft_ray_length(data, ra, r);
		ra += RAD / 16;
		ft_check_angle(&ra);
		r++;
	}
}

int		ft_display(t_cub3D *data)
{
	ft_movement(data);
	//ft_draw_bar(data);
	ft_raycast(data);
	ft_draw_walls(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	// mlx_put_image_to_window(data->mlx, data->win, data->gun, data->s_w / 2, data->s_h / 2 + FOV * 4 - 384);
	// mlx_put_image_to_window(data->mlx, data->win, data->text[0].img, 0, 0);
	// mlx_put_image_to_window(data->mlx, data->win, data->text[1].img, 64, 0);
	// mlx_put_image_to_window(data->mlx, data->win, data->text[2].img, 128, 0);
	// mlx_put_image_to_window(data->mlx, data->win, data->text[3].img, 192, 0);
	return (0);
}
