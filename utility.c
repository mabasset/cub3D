/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabasset <mabasset@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 19:04:38 by mabasset          #+#    #+#             */
/*   Updated: 2022/07/27 14:20:25 by mabasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_put_term(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	str[i] = '\0';
}

void	ft_check_angle(float *angle)
{
	if (*angle < 0)
		*angle += 2 * PI;
	if (*angle > 2 * PI)
		*angle -= 2 * PI;
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
