/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabasset <mabasset@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 16:53:49 by mabasset          #+#    #+#             */
/*   Updated: 2022/08/01 00:53:25 by mabasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "mlx/mlx.h"

# define PI		3.14159265359
# define RAD	0.0174533

//img
# define GUN	"sprites/gun.xpm"

//wallpaper color
# define WP		2383707

# define FOV	60

# define RED	16711680
# define YELLOW	16776960
# define BLUE	255
# define BLACK	0
# define WHITE	16777215
# define GREEN	65280

# define SPEED	0.1
# define SENS	0.06598132

//keypress
# define W		13
# define A		0
# define S		1
# define D		2
# define LEFT	123
# define RIGHT	124
# define ESC	53

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		e;
}				t_img;


typedef struct s_player
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	ldx;
	float	ldy;
	float	angle;
	float	langle;
	int		w;
	int		s;
	int		a;
	int		d;
	int		left;
	int		right;
}				t_player;

typedef	struct s_cub3D
{
	char		*NO;
	char		*SO;
	char		*WE;
	char		*EA;
	int			F;
	int			C;
	char		**map;
	int			height;
	int			width;
	int			s_h;
	int			s_w;
	void		*mlx;
	void		*win;
	void		*gun1;
	void		*gun2;
	void		*gun;
	float		dist[FOV * 16];
	int			color[FOV * 16];
	t_player	p;
	t_img		img;
}				t_cub3D;

//check
void	ft_check_fd(char *file_name, char *str);
void	ft_check_file(char *file_name);
void	ft_check_color(char *str);
void	ft_check_info(t_cub3D *data);
void	ft_check_map(char **map);
void	ft_check_angle(float *angle);

//read_file
void	ft_get_info(t_cub3D *data, int fd);
char	**ft_fill_map(char *str, char **matrix, int fd, char *file_name);

//init
void	ft_init_info(t_cub3D *data);
void	ft_init(t_cub3D *data);

//display
void	ft_draw_map_2d(t_cub3D *data);
int		ft_display(t_cub3D *data);

//movements
void	ft_movement(t_cub3D *data);
int		ft_on(int keycode, t_cub3D *data);
int		ft_off(int keycode, t_cub3D *data);

//utility
int		ft_skip_spaces(char *str);
char	*ft_find_map(int fd);
void	ft_print_struct(t_cub3D data);
void	ft_free_struct(t_cub3D *data);

//draw
void	my_mlx_pixel_put(t_cub3D *data, int x, int y, int color);

#endif