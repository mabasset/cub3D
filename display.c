/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabasset <mabasset@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:48:39 by mabasset          #+#    #+#             */
/*   Updated: 2022/07/27 21:42:16 by mabasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// void	ft_put_img(t_cub3D *data, char c, int x, int y)
// {
// 	if (c == '1')
// 		mlx_put_image_to_window(data->mlx, data->win, data->img.w, x, y);
// 	else if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
// 		mlx_put_image_to_window(data->mlx, data->win, data->img.f, x, y);
// }

// void	ft_draw_map_2d(t_cub3D *data)
// {
// 	int	row;
// 	int	col;

// 	row = 0;
// 	while (data->map[row] != NULL)
// 	{
// 		col = 0;
// 		while (data->map[row][col] != '\0')
// 		{
// 			ft_put_img(data, data->map[row][col], col * 16, row * 16);
// 			col++;
// 		}
// 		row++;
// 	}
// }

// void	ft_draw_cube(t_cub3D *data, float x, float y, int size)
// {
// 	float	xi;
// 	float	yi;

// 	xi = x - size;
// 	while (xi < x + size)
// 	{
// 		yi = y - size;
// 		while (yi < y + size)
// 		{
// 			mlx_pixel_put(data->mlx, data->win, xi, yi, BLUE);
// 			yi += 1;
// 		}
// 		xi += 1;
// 	}
// }

// void	ft_draw_frame(t_cub3D *data)
// {
// 	int	row;
// 	int	col;

// 	row = 0;
// 	while (row < FOV * 8)
// 	{
// 		col = 0;
// 		while (col < FOV * 16)
// 		{
// 			if (col == 0 || col == 1)
// 				my_mlx_pixel_put(data, data->s_w / 2 - FOV * 8 + col - 2, data->s_h / 2 - FOV * 4 + row, BLACK);
// 			if (col == FOV * 16 - 2 || col == FOV * 16 - 1)
// 				my_mlx_pixel_put(data, data->s_w / 2 - FOV * 8 + col + 2, data->s_h / 2 - FOV * 4 + row, BLACK);
// 			if (row == 0 || row == 1)
// 				my_mlx_pixel_put(data, data->s_w / 2 - FOV * 8 + col, data->s_h / 2 - FOV * 4 + row - 2, BLACK);
// 			if (row == FOV * 8 - 2 || row == FOV * 8 - 1)
// 				my_mlx_pixel_put(data, data->s_w / 2 - FOV * 8 + col, data->s_h / 2 - FOV * 4 + row + 2, BLACK);
// 			// if (row < FOV * 4)
// 			// 	my_mlx_pixel_put(data, data->s_w / 2 - FOV * 8 + col, data->s_h / 2 - FOV * 4 + row, data->C);
// 			// else
// 			// 	my_mlx_pixel_put(data, data->s_w / 2 - FOV * 8 + col, data->s_h / 2 - FOV * 4 + row, data->F);
// 			col++;
// 		}
// 		row++;
// 	}
// }

// void	ft_draw_rays(t_cub3D *data)
// {
// 	float	i;
// 	int		x;
// 	int		y;
// 	int		j;
// 	float	dx;
// 	float	dy;
// 	float	ra;
// 	float	ca;

// 	ra = data->p.angle - (FOV / 2) * RAD;
// 	if (ra < 0)
// 		ra += 2 * PI;
// 	j = 0;
// 	while (j < FOV * 16)
// 	{
// 		i = 0;
// 		while (i < 1000)
// 		{
// 			dx = cos(ra);
// 			dy = sin(ra);
// 			x = (int) ((data->p.x + dx * i));
// 			y = (int) ((data->p.y + dy * i));
// 			if (data->map[y][x] == '1')
// 				break ;
// 			//mlx_pixel_put(data->mlx, data->win, data->p.x + dx * i, data->p.y + dy * i, RED);
// 			i += 0.01;
// 		}
// 		ca = data->p.angle - ra;
// 		if (ca < 0)
// 			ca += 2 * PI;
// 		else if (ca > 2 * PI)
// 			ca -= 2 * PI;
// 		i *= cos(ca);
// 		data->dist[j] = i;
// 		j++;
// 		ra += RAD / 16;
// 		if (ra > 2 * PI)
// 			ra -= 2 * PI;
// 	}
// 	// j = 0;
// 	// while (j < 60)
// 	// {
// 	// 	printf("dist%d:%f\n", j, data->dist[j]);
// 	// 	j++;
// 	// }
// }

void	ft_draw_col(t_cub3D *data, float dist, int x, int color)
{
	int	i;
	
	if (dist < 1)
		dist = 1;
	i = 0;
	while (i < FOV * 4 - FOV * 4 / dist)
	{
		my_mlx_pixel_put(data, data->s_w / 2 - FOV * 8 + x, data->s_h / 2 - FOV * 4 + i, data->C);
		i++;
	}
	i = 0;
	while (i < FOV * 4 / dist)
	{
		my_mlx_pixel_put(data, data->s_w / 2 - FOV * 8 + x, data->s_h / 2 + i, color);
		my_mlx_pixel_put(data, data->s_w / 2 - FOV * 8 + x, data->s_h / 2 - i, color);
		i++;
	}
	i = 0;
	while (i < FOV * 4 - FOV * 4 / dist)
	{
		my_mlx_pixel_put(data, data->s_w / 2 - FOV * 8 + x, data->s_h / 2 + FOV * 4 - i, data->F);
		i++;
	}
}

void	ft_draw_walls(t_cub3D *data)
{
	int	i;

	i = 0;
	while (i < FOV * 16)
	{
		ft_draw_col(data, data->dist[i], i, data->color[i]);
		i++;
	}
}

// void	ft_draw_spiral(t_cub3D *data)
// {
// 	float	a;
// 	float	r;
// 	int		flag;
// 	int		color;

// 	a = 0;
// 	flag = 0;
// 	srand((unsigned) time(0));
// 	color = rand();
// 	r = 200;
// 	while (r > 0)
// 	{
// 		my_mlx_pixel_put(data, data->s_w / 2 + cos(a) * r, data->s_h / 2 + sin(a) * r, color);
// 		a += RAD / 16;
// 		if (a > 2 * PI)
// 		{
// 			a -= 2 * PI;
// 			flag = 1;
// 		}
// 		if (flag == 1)
// 			r -= 0.005;
// 	}
// }

// float	ft_ray_length(t_cub3D *data, float ra)
// {
// 	float	i;
// 	float	dx;
// 	float	dy;

// 	dx = cos(ra);
// 	dy = sin(ra);
// 	i = 0;
// 	while (data->map[(int) (data->p.y + dy * i)][(int) (data->p.x + dx * i)] != '1')
// 		i += 0.01;
// 	return (i);
// }

// int		ft_texture(void)
// {
// 	return(RED);
// }

// void	ft_raycast(t_cub3D *data)
// {
// 	float	ra;
// 	float	ca;
// 	int		r;

// 	ra = data->p.angle - FOV / 2 * RAD;
// 	ft_check_angle(&ra);
// 	r = 0;
// 	while (r < FOV * 16)
// 	{
// 		ca = data->p.angle - ra;
// 		ft_check_angle(&ca);
// 		data->dist[r] = ft_ray_length(data, ra) * cos(ca);
// 		data->color[r] = ft_texture();
// 		ra += RAD / 16;
// 		ft_check_angle(&ra);
// 		r++;
// 	}
// }

void	ft_raycast(t_cub3D *data)
{
	int		r;
	int		dof;
	float	ra;
	float	rx;
	float	ry;
	float	xo;
	float	yo;
	float	ctan;
	float	disH;
	float	disV;

	ra = data->p.angle - FOV / 2 * RAD;
	ft_check_angle(&ra);
	ctan = 1/tan(ra);
	r = 0;
	while (r < FOV * 16)
	{
		//horizontal
		dof = 0;
		if (ra > PI)
		{
			ry = (int) data->p.y;
			rx = (data->p.y - ry) * ctan + data->p.x;
			yo = -1;
			xo = yo * ctan;
		}
		if (ra < PI)
		{
			ry = ((int) data->p.y) + 1;
			rx = (data->p.y - ry) * ctan + data->p.x;
			yo = 1;
			xo = yo * ctan;
		}
		if (ra == 0 || ra == PI)
		{
			rx = data->p.x;
			ry = data->p.y;
			dof = 8;
		}
		while (dof < 8)
		{
			if (data->map[(int) ry][(int) rx] == '1')
			{
				dof = 8;
				disH = sqrt((rx - data->p.x)*(rx - data->p.x) + (ry - data->p.y)*(ry - data->p.y));
			}
			else
			{
				rx += xo;
				ry += yo;
				dof++;
			}
		}
		//vertical
		dof = 0;
		if (ra > PI / 2 && ra < 3 * PI / 2)
		{
			rx = (int) data->p.x;
			ry = (data->p.x - rx) * ctan + data->p.y;
			xo = -1;
			yo = yo * ctan;
		}
		if (ra < PI / 2 || ra > 3 * PI / 2)
		{
			rx = ((int) data->p.x) + 1;
			ry = (data->p.x - rx) * ctan + data->p.y;
			xo = 1;
			yo = xo * ctan;
		}
		if (ra == 0 || ra == PI)
		{
			rx = data->p.x;
			ry = data->p.y;
			dof = 8;
		}
		while (dof < 8)
		{
			if (data->map[(int) ry][(int) rx] == '1')
			{
				disV = sqrt((rx - data->p.x)*(rx - data->p.x) + (ry - data->p.y)*(ry - data->p.y));
				dof = 8;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof++;
			}
		}
		if (disV > disH)
			data->dist[r] = disH;
		else
			data->dist[r] = disV;
		ra += RAD / 16;
		ft_check_angle(&ra);
		r++;
	}
}

int		ft_display(t_cub3D *data)
{
	ft_movement(data);
	//ft_draw_frame(data);
	// ft_draw_rays(data);
	//ft_draw_spiral(data);
	ft_raycast(data);
	ft_draw_walls(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->gun, data->s_w / 2, data->s_h / 2 + FOV * 4 - 384);
	// if (data->s_h >= 720 && data->s_w >= 1280)
	//ft_draw_map_2d(data);
	// ft_draw_cube(data, data->p.x, data->p.y, 4);
	//mlx_put_image_to_window(data->mlx, data->win, data->img.p, data->p.x, data->p.y);
	//mlx_pixel_put(data->mlx, data->win, data->p.x, data->p.y, BLUE);
	//ft_draw_bar(data);
	//mlx_put_image_to_window(data->mlx, data->win, data->img.g, data->s_w / 2 - 128, data->s_h / 2 - 128 + FOV * 2 - 10);
	return (0);
}
