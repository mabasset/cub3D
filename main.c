/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabasset <mabasset@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 16:53:30 by mabasset          #+#    #+#             */
/*   Updated: 2022/06/21 16:27:01 by mabasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char *argv[])
{
	t_cub3D	data;

	if (argc != 2)
		ft_error("Arg");
	ft_read_file(argv[1], &data);
	ft_print_struct(data);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, 5120, 2880, "cub3D");
	ft_init(&data);
	mlx_do_key_autorepeaton(data.mlx);
	mlx_hook(data.win, 2, (1L << 1), ft_hooks, &data);
	mlx_loop_hook(data.mlx, ft_display, &data);
	mlx_loop(data.mlx);
	ft_free_struct(&data);
	return (0);
}