/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabasset <mabasset@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:41:29 by mabasset          #+#    #+#             */
/*   Updated: 2022/08/16 01:16:53 by mabasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*ft_fill_info(char *str)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	while (ft_isspace(str[i]) == 1)
		i++;
	j = 0;
	while (ft_isspace(str[i + j]) == 0)
		j++;
	str[i + j] = '\0';
	temp = (char *) malloc (sizeof(char) * (j + 1));
	ft_check_malloc(temp);
	j = 0;
	while (str[i + j] != '\0')
	{
		temp[j] = str[i + j];
		j++;
	}
	temp[j] = '\0';
	return (temp);
}

int	ft_get_color(char *str)
{
	char	**matrix;
	int		color;
	int		i;

	ft_check_color(str);
	matrix = ft_split(str, ',');
	color = 0;
	i = 0;
	while (matrix[i] != NULL)
	{
		if (ft_atoi(matrix[i]) < 0 || ft_atoi(matrix[i]) > 255)
			ft_error("Color");
		else if (i == 0)
			color += ft_atoi(matrix[i]) * 65536;
		else if (i == 1)
			color += ft_atoi(matrix[i]) * 256;
		else
			color += ft_atoi(matrix[i]);
		i++;
	}
	free(str);
	ft_free_matrix((void **) matrix);
	if (i != 3)
		ft_error("Color");
	return (color);
}

int	ft_parse_info(t_cub3D *data, char *str)
{
	if (ft_memcmp(str, "NO", 2) == 0 && data->NO == NULL)
		data->NO = ft_fill_info(str + 2);
	else if (ft_memcmp(str, "SO", 2) == 0 && data->SO == NULL)
		data->SO = ft_fill_info(str + 2);
	else if (ft_memcmp(str, "WE", 2) == 0 && data->WE == NULL)
		data->WE = ft_fill_info(str + 2);
	else if (ft_memcmp(str, "EA", 2) == 0 && data->EA == NULL)
		data->EA = ft_fill_info(str + 2);
	else if (ft_memcmp(str, "DO", 2) == 0 && data->DO == NULL)
		data->DO = ft_fill_info(str + 2);
	else if (*str == 'F' && data->F == -1)
		data->F = ft_get_color(ft_fill_info(str + 1));
	else if (*str == 'C' && data->C == -1)
		data->C = ft_get_color(ft_fill_info(str + 1));
	else
		return (0);
	return (1);
}

void	ft_get_info(t_cub3D *data, int fd)
{
	char	*str;
	int		i;

	i = 0;
	str = get_next_line(fd);
	while (str != NULL)
	{
		i = ft_skip_spaces(str);
		if (str[i] == '1')
		{
			free(str);
			break ;
		}
		if (str[i] != '\0')
			if (ft_parse_info(data, str + i) == 0)
				ft_error("Info");
		free(str);
		str = get_next_line(fd);
	}
}

char	**ft_fill_map(char *str, char **matrix, int fd, char *file_name)
{
	int		i;

	i = 0;
	while (str != NULL)
	{
		i++;
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	matrix = (char **) malloc (sizeof(char *) * (i + 1));
	ft_check_malloc(matrix);
	matrix[i] = NULL;
	fd = open(file_name, O_RDONLY);
	str = ft_find_map(fd);
	i = -1;
	while (str != NULL)
	{
		if (str[ft_strlen(str) - 1] == '\n')
			str[ft_strlen(str) - 1] = '\0';
		matrix[++i] = str;
		str = get_next_line(fd);
	}
	close(fd);
	return (matrix);
}
