NAME = cub3D
SRC = main.c read_file.c init.c movements.c display.c utility.c
FLG = -Wall -Wextra -Werror
MLX_FLG = -l mlx -framework openGL -framework AppKit

$(NAME):
		make -C libft
		gcc $(MLX_FLG) $(SRC) -o $(NAME) libft/libft.a

clean:
		rm -rf $(NAME)

fclean:	clean
		make fclean -C libft

all:	$(NAME)

re:		fclean all