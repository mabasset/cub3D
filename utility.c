/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabasset <mabasset@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 19:04:38 by mabasset          #+#    #+#             */
/*   Updated: 2022/06/20 14:44:39 by mabasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_print_struct(t_cub3D data)
{
	int	row;

	ft_printf("NO: %s\n", data.NO);
	ft_printf("SO: %s\n", data.SO);
	ft_printf("WE: %s\n", data.WE);
	ft_printf("EA: %s\n", data.EA);
	ft_printf("F: %s\n", data.F);
	ft_printf("C: %s\n", data.C);
	row = 0;
	while (data.map[row] != NULL)
	{
		ft_printf("%s\n", data.map[row]);
		row++;
	}
	ft_printf("height: %d\n", data.height);
}

void	ft_free_struct(t_cub3D *data)
{
	free(data->NO);
	free(data->SO);
	free(data->WE);
	free(data->EA);
	free(data->F);
	free(data->C);
	ft_free_matrix((void **)data->map);
}
