/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabasset <mabasset@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:59:31 by mabasset          #+#    #+#             */
/*   Updated: 2022/07/30 19:19:50 by mabasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_check_fd(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd <= 0)
		ft_error("Map file");
	close(fd);
}

void	ft_check_file(char *file_name)
{
	if (ft_strlen(file_name) < 5)
		ft_error("Map name");
	if (ft_memcmp(&file_name[ft_strlen(file_name) - 4], ".cup", 4) != 0)
		ft_error("Map extension");
	ft_check_fd(file_name);
}

void	ft_check_color(char *str)
{
	int	i;
	
	ft_error("Color");
}

void	ft_check_info(t_cub3D *data)
{
	if (data->NO == NULL || data->SO == NULL || data->WE == NULL)
		ft_error("Info");
	if (data->EA == NULL || data->F == -1 || data->C == -1)
		ft_error("Info");
	// ft_check_fd(data->NO);
	// ft_check_fd(data->SO);
	// ft_check_fd(data->WE);
	// ft_check_fd(data->EA);
}

void	ft_check_angle(float *angle)
{
	if (*angle < 0)
		*angle += 2 * PI;
	if (*angle > 2 * PI)
		*angle -= 2 * PI;
}