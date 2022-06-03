/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:11:42 by tnaton            #+#    #+#             */
/*   Updated: 2022/06/03 16:13:30 by bdetune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIN_HEIGHT 1350
# define WIN_WIDTH 2550
# define PROJ_PLANE_DIST 1
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <math.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# define WIDTH 1920
# define HEIGHT 1080
# define STEP 0.25

typedef struct s_map
{
	char			*ligne;
	struct s_map	*next;
}	t_map;

typedef struct s_texture
{
	void	*texture;
	int		width;
	int		height;
	char	*path;
} t_texture;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
} t_img;

typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
} t_player;

typedef struct s_info
{
	void			*mlx;
	void			*win;
	t_img			img;
	int				printerr;
	t_texture		no;
	t_texture		so;
	t_texture		we;
	t_texture		ea;
	unsigned int	f;
	unsigned int	c;
	t_map			*lstmap;
	char			**map;
	char			dir;
	t_player		player;
}	t_info;

int				charinstr(char *str, char c);
int				substrinstr(char *str, char *substr);
char			*getlaststr(char *ligne);
t_info			getinfo(t_map *map);
unsigned int	getlist(char *str);
char			**parsemap(t_map *lstmap);
void			freecharchar(char **lst);
void			puterr(char *str, t_info *info);
void			freelstmap(t_map *map);
int				mlx(t_info *info);
void			freeallchunk(t_map *map);
void			freeinfo(t_info *info);
void			loop(t_info *info);

#endif
