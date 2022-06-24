/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabasset <mabasset@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:48:39 by mabasset          #+#    #+#             */
/*   Updated: 2022/06/24 16:17:28 by mabasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_put_img(t_cub3D *data, char c, int x, int y)
{
	if (c == '1')
		mlx_put_image_to_window(data->mlx, data->win, data->img.w, x, y);
	else if (c == '0')
		mlx_put_image_to_window(data->mlx, data->win, data->img.f, x, y);
}

void	ft_draw_map_2d(t_cub3D *data)
{
	int	row;
	int	col;

	row = 0;
	while (data->map[row] != NULL)
	{
		col = 0;
		while (data->map[row][col] != '\0')
		{
			ft_put_img(data, data->map[row][col], col * 64, row * 64);
			col++;
		}
		row++;
	}
}

void	ft_draw_cube(t_cub3D *data, float x, float y, int size)
{
	float	xi;
	float	yi;

	xi = x - size;
	while (xi < x + size)
	{
		yi = y - size;
		while (yi < y + size)
		{
			mlx_pixel_put(data->mlx, data->win, xi, yi, BLUE);
			yi += 1;
		}
		xi += 1;
	}
}

void	ft_draw_rays(t_cub3D *data)
{
// 	int		mx;
// 	int		my;
// 	int		dof;
// 	float	rx;
// 	float	ry;
// 	float	xo;
// 	float	yo;

// 	dof = 0;
// //horizontal
// 	//look up
// 	if (data->p.a < PI)
// 	{
// 		ry = (((int) data->p.y >> 6) << 6) + 64;
// 		rx = (ry - data->p.y) * (1/tan(data->p.a)) + data->p.x;
// 		yo = 64;
// 		xo = yo * (1/tan(data->p.a));
// 	}
// 	//look down
// 	if (data->p.a > PI)
// 	{
// 		ry = (((int) data->p.y >> 6) << 6);
// 		rx = (ry - data->p.y) * (1/tan(data->p.a)) + data->p.x;
// 		yo = -64;
// 		xo = yo * (1/tan(data->p.a));
// 	}
// 	if (data->p.a == 0 || data->p.a == PI)
// 	{
// 		rx = data->p.x;
// 		ry = data->p.y;
// 		dof = 8;
// 	}
	// printf ("pa:%f\n", data->p.a);
	// while (dof < 8)
	// {
	// 	mx = (int) (rx) >> 6;
	// 	my = (int) (ry) >> 6;
	// 	printf ("mx:%d\n", mx);
	// 	printf ("my:%d\n", my);
	// 	if ((mx < 33 && my < data->height) && data->map[mx][my] == '1')
	// 	{
	// 		dof = 8;
	// 		printf ("ciao\n");
	// 	}
	// 	else
	// 	{
	// 		rx += xo;
	// 		ry += yo;
	// 		dof += 1;
	// 	}
	// }

	//ft_draw_cube(data, rx, ry, 2);
	
//vertical
	//look right
	// if (data->p.a > P2 && data->p.a < P3)
	// {
	// 	rx = (((int) data->p.x >> 6) << 6);
	// 	ry = (rx - data->p.x) * tan(data->p.a) + data->p.y;
	// 	xo = -64;
	// 	yo = xo * tan(data->p.a);
	// }
	// //look left
	// if (data->p.a < P2 || data->p.a > P3)
	// {
	// 	rx = (((int) data->p.x >> 6) << 6) + 64;
	// 	ry = (rx - data->p.x) * tan(data->p.a) + data->p.y;
	// 	xo = 64;
	// 	yo = xo * tan(data->p.a);
	// }

	// dof = 0;
	// while (dof < 8)
	// {
	// 	mx = (int) (rx) >> 6;
	// 	my = (int) (ry) >> 6;
	// 	printf ("mx:%d\n", mx);
	// 	printf ("my:%d\n", my);
	// 	if ((mx < 33 && my < data->height) && data->map[mx][my] == '1')
	// 		dof = 8;
	// 	else
	// 	{
	// 		rx += xo;
	// 		ry += yo;
	// 		dof += 1;
	// 	}
	// }

	//ft_draw_cube(data, rx, ry, 2);

	float	i;
	int		x;
	int		y;
	float	dx;
	float	dy;
	float	ra;

	i = 0;
	//printf ("pa:%f\n", data->p.a);
	while (i < 1000)
	{
		x = (int) ((data->p.x + data->p.dx * i) / 64);
		y = (int) ((data->p.y + data->p.dy * i) / 64);
		dx = cos(data->p.a);
		dy = sin(data->p.a);
		if (data->map[y][x] == '1')
			break ;
		mlx_pixel_put(data->mlx, data->win, data->p.x + dx * i, data->p.y + dy * i, RED);
		i += 0.1;
	}
	i = 0;
	while (i < 1000)
	{
		x = (int) ((data->p.x + dx * i) / 64);
		y = (int) ((data->p.y + dy * i) / 64);
		ra = data->p.a - P2 / 3;
		if (ra < 0)
			ra += 2 * PI;
		dx = cos(ra);
		dy = sin(ra);
		if (data->map[y][x] == '1')
			break ;
		//mlx_pixel_put(data->mlx, data->win, data->p.x + dx * i, data->p.y + dy * i, RED);
		i += 0.1;
	}
	i = 0;
	while (i < 1000)
	{
		x = (int) ((data->p.x + dx * i) / 64);
		y = (int) ((data->p.y + dy * i) / 64);
		ra = data->p.a + P2 / 2;
		if (ra > 2 * PI)
			ra -= 2 * PI;
		dx = cos(ra);
		dy = sin(ra);
		if (data->map[y][x] == '1')
			break ;
		//mlx_pixel_put(data->mlx, data->win, data->p.x + dx * i, data->p.y + dy * i, RED);
		i += 0.1;
	}
	// i = 0;
	// while (i < 1000)
	// {
	// 	x = (int) ((data->p.x + data->p.dx * i) / 64);
	// 	y = (int) ((data->p.y + data->p.dy * i) / 64);
	// 		if (data->p.a < 0)
	// 	dx = cos(data->p.a + PI / 4) * 5;
	// 	dy = cos(data->p.a + PI / 4) * 5;
	// 	if (data->map[y][x] == '1')
	// 		break ;
	// 	mlx_pixel_put(data->mlx, data->win, data->p.x - dx * i, data->p.y - dy * i, RED);
	// 	i += 0.1;
	// }
}

int		ft_display(t_cub3D *data)
{
	mlx_clear_window(data->mlx, data->win);
	ft_draw_map_2d(data);
	ft_draw_cube(data, data->p.x, data->p.y, 5);
	ft_draw_rays(data);
	return (0);
}
