/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabasset <mabasset@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:59:31 by mabasset          #+#    #+#             */
/*   Updated: 2022/08/01 01:21:36 by mabasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_check_fd(char *file_name, char *str)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd <= 0)
	{
		ft_printf("%s ", str);
		ft_error("file");
	}
	close(fd);
}

void	ft_check_file(char *file_name)
{
	if (ft_strlen(file_name) < 5)
		ft_error("Map name");
	if (ft_memcmp(&file_name[ft_strlen(file_name) - 4], ".cup", 4) != 0)
		ft_error("Map extension");
	ft_check_fd(file_name, "Map");
}

void	ft_check_color(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0 && str[i] != ',')
			ft_error("Color");
		if (str[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
		ft_error("Color");
}

void	ft_check_info(t_cub3D *data)
{
	if (data->NO == NULL || data->SO == NULL || data->WE == NULL)
		ft_error("Info");
	if (data->EA == NULL || data->F < 0 || data->C < 0)
		ft_error("Info");
	ft_check_fd(data->NO, "Texture");
	ft_check_fd(data->SO, "Texture");
	ft_check_fd(data->WE, "Texture");
	ft_check_fd(data->EA, "Texture");
}
