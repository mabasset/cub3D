/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabasset <mabasset@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 19:04:38 by mabasset          #+#    #+#             */
/*   Updated: 2022/07/30 19:13:19 by mabasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]) == 1)
		i++;
	return (i);
}

char	*ft_find_map(int fd)
{
	char	*str;
	int		i;

	str = get_next_line(fd);
	while(str != NULL)
	{
		i = 0;
		while (ft_isspace(str[i]) == 1)
			i++;
		if (str[i] == '1')
			return (str);
		free(str);
		str = get_next_line(fd);
	}
	ft_error("Map");
	return (NULL);
}

void	ft_print_struct(t_cub3D data)
{
	int	row;

	ft_printf("NO: %s\n", data.NO);
	ft_printf("SO: %s\n", data.SO);
	ft_printf("WE: %s\n", data.WE);
	ft_printf("EA: %s\n", data.EA);
	ft_printf("F: %d\n", data.F);
	ft_printf("C: %d\n", data.C);
	row = 0;
	while (data.map[row] != NULL)
	{
		ft_printf("%s\n", data.map[row]);
		row++;
	}
}

void	ft_free_struct(t_cub3D *data)
{
	free(data->NO);
	free(data->SO);
	free(data->WE);
	free(data->EA);
	ft_free_matrix((void **)data->map);
}
