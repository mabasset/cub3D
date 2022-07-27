/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabasset <mabasset@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:41:29 by mabasset          #+#    #+#             */
/*   Updated: 2022/07/25 19:57:19 by mabasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*ft_get_row(char *str, int flag)
{
	int		i;
	char	*tmp;

	ft_put_term(str);
	tmp = malloc (sizeof(char) * (ft_strlen(str) - flag));
	i = flag;
	while (str[i] != '\0')
	{
		tmp[i - flag] = str[i];
		i++;
	}
	tmp[i - flag] = '\0';
	free(str);
	return (tmp);
}

int		ft_get_color(char *str)
{
	char	**matrix;
	int		color;
	int		multiplier;
	int		i;

	ft_put_term(str);
	matrix = ft_split(str, ',');
	color = 0;
	i = 0;
	while (matrix[i] != NULL)
	{
		if (ft_atoi(matrix[i]) != 0)
		{
			if (i == 0)
				multiplier = 65536;
			else if (i == 1)
				multiplier = 256;
			else
				multiplier = 1;
			color += ft_atoi(matrix[i]) * multiplier;
		}
		i++;
	}
	return (color);
}

void	ft_get_info(int fd, char *str, t_cub3D *data)
{
	str = get_next_line(fd);
	data->NO = ft_get_row(str, 3);
	str = get_next_line(fd);
	data->SO = ft_get_row(str, 3);
	str = get_next_line(fd);
	data->WE = ft_get_row(str, 3);
	str = get_next_line(fd);
	data->EA = ft_get_row(str, 3);
	str = get_next_line(fd);
	free(str);
	str = get_next_line(fd);
	data->F = ft_get_color(&str[2]);
	str = get_next_line(fd);
	data->C = ft_get_color(&str[2]);
	str = get_next_line(fd);
	free(str);
}

int		ft_get_height(char *file_name, char *str)
{
	int		height;
	int		fd;

	fd = open(file_name, O_RDONLY);
	str = get_next_line(fd);
	height = 0;
	while (str != NULL)
	{
		height++;
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (height - 8);
}

void	ft_read_file(char *file_name, t_cub3D *data)
{
	int		fd;
	int		row;
	char	*str;

	fd = open(file_name, O_RDONLY);
	str = NULL;
	ft_get_info(fd, str, data);
	data->height = ft_get_height(file_name, str);
	data->map = (char **) malloc (sizeof(char *) * (data->height + 1));
	data->map[data->height] = NULL;
	row = 0;
	while (row < data->height)
	{
		str = get_next_line(fd);
		data->map[row] = ft_get_row(str, 0);
		row++;
	}
	close(fd);
}
