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
		//data->hit_y[i] += text->h / 2 / data->wall_h[i];
		color = *(unsigned int *)src;
		*(unsigned int *)dst = color;
	}
}

void	ft_draw_col(t_cub3D *data, float wall_h, int x, t_text *text)
{
	int	y;
	int	win_h;
	int	ceal_h;

	win_h = FOV * 8;
	if (wall_h > win_h)
		wall_h = win_h;
	y = 0;
	ceal_h = (win_h - wall_h) / 2;
	while (y < ceal_h)
	{
		my_mlx_pixel_put(data, data->s_w / 2 - FOV * 8 + x, data->s_h / 2 - win_h / 2 + y, data->C);
		y++;
	}
	while (y < wall_h + ceal_h)
	{
		//my_mlx_pixel_put(data, data->s_w / 2 - FOV * 8 + x, data->s_h / 2 - win_h / 2 + y, RED);
		text_pixel_put(data, data->s_w / 2 - FOV * 8 + x, data->s_h / 2 - win_h / 2 + y, text, x, y - ceal_h);
		y++;
	}
	while (y < win_h)
	{
		my_mlx_pixel_put(data, data->s_w / 2 - FOV * 8 + x, data->s_h / 2 - win_h / 2 + y, data->F);
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

float	ft_wall_info(t_cub3D *data, float ra, int r)
{
	float	dist;
	float	dx;
	float	dy;
	float	fish_eye;

	dx = cos(ra);
	dy = sin(ra);
	dist = 0;
	while (data->map[(int) (data->p.y + dy * dist)][(int) (data->p.x + dx * dist)] != '1')
		dist += 0.01;
	data->orientation[r] = ft_orientation(data, ra, dist);
	if (data->orientation[r] == 1)
		data->hit_x[r] = floor(((data->p.x + dx * dist) - floor(data->p.x + dx * dist)) * 64);
	else if (data->orientation[r] == 2)
		data->hit_x[r] = 64 - floor(((data->p.x + dx * dist) - floor(data->p.x + dx * dist)) * 64);
	else if (data->orientation[r] == 3)
		data->hit_x[r] = 64 - floor(((data->p.y + dy * dist) - floor(data->p.y + dy * dist)) * 64);
	else
		data->hit_x[r] = floor(((data->p.y + dy * dist) - floor(data->p.y + dy * dist)) * 64);
	fish_eye = data->p.angle - ra;
	ft_check_angle(&fish_eye);
	dist *= cos(fish_eye);
	return (FOV * 8 / dist);
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

void	ft_mouse(t_cub3D *data)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(data->win, &x, &y);
	if (x < data->s_w / 2)
		data->p.left = 1;
	else if (x > data->s_w / 2)
		data->p.right = 1;
	else
	{
		data->p.left = 0;
		data->p.right = 0;
	}
}

int		ft_display(t_cub3D *data)
{
	data->frame += 1;
	//ft_mouse(data);
	ft_movement(data);
	//ft_draw_bar(data);
	ft_raycast(data);
	ft_draw_walls(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	data->s.gun = data->s.gun1;
	if (data->frame > 20)
		data->s.gun = data->s.gun2;
	if (data->frame == 40)
		data->frame = 0;
	mlx_put_image_to_window(data->mlx, data->win, data->s.gun, data->s_w / 2, data->s_h / 2 + FOV * 4 - 384);
	// mlx_put_image_to_window(data->mlx, data->win, data->text[0].img, 0, 0);
	// mlx_put_image_to_window(data->mlx, data->win, data->text[1].img, 64, 0);
	// mlx_put_image_to_window(data->mlx, data->win, data->text[2].img, 128, 0);
	// mlx_put_image_to_window(data->mlx, data->win, data->text[3].img, 192, 0);
	return (0);
}
