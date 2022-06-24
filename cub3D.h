/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabasset <mabasset@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 16:53:49 by mabasset          #+#    #+#             */
/*   Updated: 2022/06/21 19:29:13 by mabasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"

# define PI		3.14159265359
# define P2		PI/2
# define P3		3*P2

# define PLAYER	"sprites/player.xpm"
# define WALL	"sprites/wall.xpm"
# define FLOOR	"sprites/floor.xpm"

# define RED 16711680
# define YELLOW 65025
# define BLUE 255
# define BLACK 0
# define WHITE 16777215
# define GREEN 65280

typedef struct s_img
{
	void	*p;
	void	*w;
	void	*f;
}				t_img;

typedef struct s_player
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	a;
}				t_player;

typedef	struct s_cub3D
{
	char		*NO;
	char		*SO;
	char		*WE;
	char		*EA;
	char		*F;
	char		*C;
	char		**map;
	int			height;
	int			width;
	void		*mlx;
	void		*win;
	t_player	p;
	t_img		img;
}				t_cub3D;

//read_file
void	ft_read_file(char *file_name, t_cub3D *data);

//init
void	ft_init(t_cub3D *data);

//display
void	ft_draw_map_2d(t_cub3D *data);
int		ft_display(t_cub3D *data);

//movements
int		ft_hooks(int keycode, t_cub3D *data);

//utility
void	ft_print_struct(t_cub3D data);
void	ft_free_struct(t_cub3D *data);


#endif