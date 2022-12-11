/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabasset <mabasset@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:48:39 by mabasset          #+#    #+#             */
/*   Updated: 2022/09/26 21:29:22 by mabasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	text_pixel_put(t_cub3D *data, int x, int y, t_text *text, int i, int tex_y)
{
	char	*dst;
	char	*src;
	int		color;

	dst = data->img.addr + (y * data->img.ll + x * (data->img.bpp / 8));
	if (data->wall_h[i] > FOV * 8)
		tex_y += (floor(data->wall_h[i] - FOV * 8) / 2);
	if (text == NULL)
		*(unsigned int *)dst = BLACK;
	else
	{
		src = text->addr + ((int)(tex_y * text->h / data->wall_h[i]) * text->ll + (int)data->hit_x[i] * (text->bpp / 8));
		color = *(unsigned int *)src;
		*(unsigned int *)dst = color;
	}
}

void	ft_draw_col(t_cub3D *data, float wall_h, int x, t_text *text)
{
	int	y;
	int	xo;
	int	yo;

	if (wall_h > FOV * 8)
		wall_h = FOV * 8;
	xo = data->s_w / 2 - FOV * 8;
	yo = data->s_h / 2 - FOV * 4;
	y = 0;
	while (y < (FOV * 8 - wall_h) / 2)
	{
		my_mlx_pixel_put(data, xo + x, yo + y, data->C);
		y++;
	}
	while (y < wall_h + (FOV * 8 - wall_h) / 2)
	{
		text_pixel_put(data, xo + x, yo + y, text, x, y - (FOV * 8 - wall_h) / 2);
		y++;
	}
	while (y < FOV * 8)
	{
		my_mlx_pixel_put(data, xo + x, yo + y, data->F);
		y++;
	}
}

void	ft_draw_walls(t_cub3D *data)
{
	int	i;

	i = 0;
	while (i < FOV * 16)
	{
		if (data->orientation[i] == 1)
			ft_draw_col(data, data->wall_h[i], i, &data->text[0]);
		else if (data->orientation[i] == 2)
			ft_draw_col(data, data->wall_h[i], i, &data->text[1]);
		else if (data->orientation[i] == 3)
			ft_draw_col(data, data->wall_h[i], i, &data->text[2]);
		else if (data->orientation[i] == 4)
			ft_draw_col(data, data->wall_h[i], i, &data->text[3]);
		else if (data->orientation[i] >= 5 && data->orientation[i] <= 8)
			ft_draw_col(data, data->wall_h[i], i, &data->text[4]);
		else
			ft_draw_col(data, data->wall_h[i], i, NULL);
		i++;
	}
}
int	ft_door_orientation(t_cub3D *data, float ra, float dist)
{
	if (data->map[(int)(y - 0.01)][(int) x] == '1')
		return (5);
	else if (data->map[(int)(y + 0.01)][(int) x] == '1')
		return (6);
	else if (data->map[(int) y][(int)(x - 0.01)] == '1')
		return (7);
	else if (data->map[(int) y][(int)(x + 0.01)] == '1')
		return (8);
	return (9);
}

int	ft_orientation(t_cub3D *data, float ra, float dist)
{
	float	y;
	float	x;

	dist -= 0.01;
	x = data->p.x + cos(ra) * dist;
	y = data->p.y + sin(ra) * dist;
	if (data->map[(int)(y - 0.01)][(int) x] == '1')
		return (1);
	else if (data->map[(int)(y + 0.01)][(int) x] == '1')
		return (2);
	else if (data->map[(int) y][(int)(x - 0.01)] == '1')
		return (3);
	else if (data->map[(int) y][(int)(x + 0.01)] == '1')
		return (4);
	else
		return (ft_door_orientation(data, x, y));
}

void	ft_door_x(t_cub3D *data, int r, float y, float x)
{
	if (data->orientation[r] == 5)
		data->hit_x[r] = floor((x - floor(x)) * data->text[4].w);
	else if (data->orientation[r] == 6)
		data->hit_x[r] = data->text[1].w - floor((x - floor(x)) * data->text[4].w);
	else if (data->orientation[r] == 7)
		data->hit_x[r] = data->text[4].w - floor((y - floor(y)) * data->text[4].w);
	else if (data->orientation[r] == 8)
		data->hit_x[r] = floor((y - floor(y)) * data->text[4].w);
}

void	ft_text_x(t_cub3D *data, int r, float y, float x)
{
	if (data->orientation[r] == 1)
		data->hit_x[r] = floor((x - floor(x)) * data->text[0].w);
	else if (data->orientation[r] == 2)
		data->hit_x[r] = data->text[1].w - floor((x - floor(x)) * data->text[1].w);
	else if (data->orientation[r] == 3)
		data->hit_x[r] = data->text[2].w - floor((y - floor(y)) * data->text[2].w);
	else if (data->orientation[r] == 4)
		data->hit_x[r] = floor((y - floor(y)) * data->text[3].w);
	else
		ft_door_x(data, r, y, x);
}

float	ft_wall_info(t_cub3D *data, float ra, int r, float dist)
{
	float	dx;
	float	dy;
	float	x;
	float	y;

	dx = cos(ra);
	dy = sin(ra);
	dist = 0.0;
	while (1)
	{
		y = data->p.y + dy * dist;
		x = data->p.x + dx * dist;
		if (data->map[(int) y][(int) x] == '1' || data->map[(int) y][(int) x] == 'D')
			break ;
		dist += 0.01;
	}
	data->orientation[r] = ft_orientation(data, ra, dist);
	ft_text_x(data, r, y, x);
	if (data->map[(int) y][(int) x] == 'D')
		data->orientation[r] = 5;
	ra = data->p.angle - ra;
	ft_check_angle(&ra);
	return (FOV * 8 / (dist * cos(ra)));
}

int	ft_display(t_cub3D *data)
{
	float	ra;
	int		r;

	ft_movement(data);
	ra = data->p.angle - FOV / 2 * RAD;
	ft_check_angle(&ra);
	r = 0;
	while (r < FOV * 16)
	{
		data->wall_h[r] = ft_wall_info(data, ra, r, 0.0);
		ra += RAD / 16;
		ft_check_angle(&ra);
		r++;
	}
	ft_draw_walls(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}
