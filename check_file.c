/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabasset <mabasset@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:59:31 by mabasset          #+#    #+#             */
/*   Updated: 2022/07/26 19:10:08 by mabasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_remove_newline(char *file_name)
{
	int		fd;
	char	buf[1];

	fd = open(file_name, O_RDWR);
	while(read(fd, buf, 1) != 0)
	{
		if (*buf == '\n')
			write(fd, "\0", 1);
	}
}

void	ft_check_file(char *file_name)
{
	int	fd;

	if (ft_strlen(file_name) < 5)
		ft_error("File name");
	if (ft_memcmp(&file_name[ft_strlen(file_name) - 4], ".cup", 4) != 0)
		ft_error("Extension");
	fd = open(file_name, O_RDONLY);
	if (fd <= 0)
		ft_error("File name");
	close(fd);
	//ft_remove_newline(file_name);
}