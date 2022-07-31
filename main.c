/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabasset <mabasset@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 16:53:30 by mabasset          #+#    #+#             */
/*   Updated: 2022/08/01 01:24:46 by mabasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_read_file(char *file_name, t_cub3D *data)
{
	int		fd;
	int		i;
	char	*str;
	char	**matrix;

	ft_init_info(data);
	fd = open(file_name, O_RDONLY);
	ft_get_info(data, fd);
	ft_check_info(data);
	close(fd);
	fd = open(file_name, O_RDONLY);
	str = ft_find_map(fd);
	matrix = NULL;
	data->map = ft_fill_map(str, matrix, fd, file_name);
	ft_check_map(data->map);
	close(fd);
}

int	main(int argc, char *argv[])
{
	t_cub3D	data;

	if (argc != 2)
		ft_error("Arg");
	ft_check_file(argv[1]);
	ft_read_file(argv[1], &data);
	ft_print_struct(data);
	data.mlx = mlx_init();
	mlx_get_screen_size(data.mlx, &data.s_w, &data.s_h);
	data.win = mlx_new_window(data.mlx, data.s_w, data.s_h, "cub3D");
	ft_init(&data);
	mlx_do_key_autorepeaton(data.mlx);
	mlx_hook(data.win, 2, 0, ft_on, &data);
	mlx_hook(data.win, 3, 0, ft_off, &data);
	mlx_loop_hook(data.mlx, ft_display, &data);
	mlx_loop(data.mlx);
	ft_free_struct(&data);
	return (0);
}
