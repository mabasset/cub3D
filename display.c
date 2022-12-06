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
		src = text->addr + ((int) (tex_y * text->h / data->wall_h[i]) * text->ll + (int)data->hit_x[i] * (text->bpp / 8));
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
		else
			ft_draw_col(data, data->wall_h[i], i, NULL);
		i++;
	}
}

int		ft_orientation(t_cub3D *data, float ra, float dist)
{
	float	y;
	float	x;

	dist -= 0.01;
	x = data->p.x + cos(ra) * dist;
	y = data->p.y + sin(ra) * dist;
	if (data->map[(int) (y - 0.01)][(int) x] == '1')
		return(1);
	else if (data->map[(int) (y + 0.01)][(int) x] == '1')
		return(2);
	else if (data->map[(int) y][(int) (x - 0.01)] == '1')
		return(3);
	else if (data->map[(int) y][(int) (x + 0.01)] == '1')
		return(4);
	return (5);
}

float	ft_wall_info(t_cub3D *data, float ra, int r)
{
	float	dist;
	float	x;
	float	y;

	dist = 0.0;
	while (1)
	{
		y = data->p.y + sin(ra) * dist;
		x = data->p.x + cos(ra) * dist;
		if (data->map[(int) y][(int) x] == '1')
			break ;
		dist += 0.01;
	}
	data->orientation[r] = ft_orientation(data, ra, dist);
	if (data->orientation[r] == 1)
		data->hit_x[r] = floor((x - floor(x)) * 64);
	else if (data->orientation[r] == 2)
		data->hit_x[r] = 64 - floor((x - floor(x)) * 64);
	else if (data->orientation[r] == 3)
		data->hit_x[r] = 64 - floor((y - floor(y)) * 64);
	else
		data->hit_x[r] = floor((y - floor(y)) * 64);
	ra = data->p.angle - ra;
	ft_check_angle(&ra);
	return (FOV * 8 / (dist * cos(ra)));
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
		data->wall_h[r] = ft_wall_info(data, ra, r);
		ra += RAD / 16;
		ft_check_angle(&ra);
		r++;
	}
}

int		ft_display(t_cub3D *data)
{
	data->frame += 1;
	ft_movement(data);
	//ft_draw_bar(data);
	ft_raycast(data);
	ft_draw_walls(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	//mlx_put_image_to_window(data->mlx, data->win, data->s.hand, data->s_w / 2, data->s_h / 2 + FOV * 4 - 384);
	//mlx_put_image_to_window(data->mlx, data->win, data->s.ari, data->s_w / 2 - FOV * 8 - 17, data->s_h / 2 + 22);
	return (0);
}
