/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabasset <mabasset@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:42:57 by mabasset          #+#    #+#             */
/*   Updated: 2022/07/28 18:11:19 by mabasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_on(int keycode, t_cub3D *data)
{
	int	x;
	int	y;

	if (keycode == ESC)
		exit(0);
	if (keycode == W)
		data->p.w = 1;
	if (keycode == A)
		data->p.a = 1;
	if (keycode == S)
		data->p.s = 1;
	if (keycode == D)
		data->p.d = 1;
	if (keycode == LEFT)
		data->p.left = 1;
	if (keycode == RIGHT)
		data->p.right = 1;
	return (0);
}

int	ft_off(int keycode, t_cub3D *data)
{
	int	x;
	int	y;

	if (keycode == ESC)
		exit(0);
	if (keycode == W)
		data->p.w = 0;
	 if (keycode == A)
	 	data->p.a = 0;
	if (keycode == S)
	 	data->p.s = 0;
	if (keycode == D)
	 	data->p.d = 0;
	if (keycode == LEFT)
		data->p.left = 0;
	if (keycode == RIGHT)
		data->p.right = 0;
	return (0);
}

void	ft_move(t_cub3D	*data, float move_x, float move_y)
{
	float	i;

	i = (data->p.x + move_x);
	if (data->map[(int) data->p.y][(int) i] != '1')
		data->p.x += move_x;
	i = (data->p.y + move_y);
	if (data->map[(int) i][(int) data->p.x] != '1')
		data->p.y += move_y;
}

void	ft_dir(t_cub3D *data, float dir)
{
	data->p.angle += dir;
	ft_check_angle(&data->p.angle);
	data->p.dx = cos(data->p.angle);
	data->p.dy = sin(data->p.angle);
}

void	ft_movement(t_cub3D *data)
{
	float	langle;
	float	ldx;
	float	ldy;
	int		x;
	int		y;

	mlx_mouse_hide();
	mlx_mouse_get_pos(data->win, &x, &y);
	langle = data->p.angle - PI / 2;
	ft_check_angle(&langle);
	ldx = cos(langle);
	ldy = sin(langle);
	if (data->p.w == 1)
		ft_move(data, data->p.dx * SPEED, data->p.dy * SPEED);
	if (data->p.s == 1)
		ft_move(data, -(data->p.dx * SPEED), -(data->p.dy * SPEED));
	if (data->p.a == 1)
		ft_move(data, ldx * SPEED, ldy * SPEED);
	if (data->p.d == 1)
		ft_move(data, -(ldx * SPEED), -(ldy * SPEED));
	if (data->p.left == 1 || x < data->s_w / 2)
		ft_dir(data, -SENS);
	if (data->p.right == 1 || x > data->s_w / 2)
		ft_dir(data, SENS);
	mlx_mouse_move(data->win, data->s_w / 2, data->s_h / 2);
}
