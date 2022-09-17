/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabasset <mabasset@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 16:20:21 by mabasset          #+#    #+#             */
/*   Updated: 2022/08/01 15:32:05 by mabasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_check_spaces(char **map, int row, int col)
{
	if (map[row - 1][col] == ' ' || map[row - 1][col] == '\0')
		ft_error("Map");
	if (map[row + 1][col] == ' ' || map[row + 1][col] == '\0')
		ft_error("Map");
	if (map[row][col - 1] == ' ' || map[row][col - 1] == '\0')
		ft_error("Map");
	if (map[row][col - 1] == ' ' || map[row][col + 1] == '\0')
		ft_error("Map");
	if (map[row - 1][col - 1] == ' ' || map[row - 1][col - 1] == '\0')
		ft_error("Map");
	if (map[row + 1][col + 1] == ' ' || map[row + 1][col + 1] == '\0')
		ft_error("Map");
	if (map[row - 1][col + 1] == ' ' || map[row - 1][col + 1] == '\0')
		ft_error("Map");
	if (map[row + 1][col - 1] == ' ' || map[row + 1][col - 1] == '\0')
		ft_error("Map");
}

void	ft_check_map(char **map)
{
	int		row;
	int		col;
	int		count;
	char	c;

	count = 0;
	row = 0;
	while (map[row] != NULL)
	{
		col = 0;
		while (map[row][col] != '\0')
		{
			c = map[row][col];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				count++;
			if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
				ft_check_spaces(map, row, col);
			else if (c != '1' && c != ' ')
				ft_error("Map");
			col++;
		}
		row++;
	}
	if (count != 1)
		ft_error("Map");
}

void	ft_check_angle(float *angle)
{
	if (*angle < 0)
		*angle += 2 * PI;
	if (*angle > 2 * PI)
		*angle -= 2 * PI;
}
