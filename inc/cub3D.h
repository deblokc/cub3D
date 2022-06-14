/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:11:42 by tnaton            #+#    #+#             */
/*   Updated: 2022/06/13 18:49:37 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define PROJ_PLANE_DIST 1
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <math.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/time.h>
# include <time.h>
# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# define NB_IMG 16
# define STEP 0.25

typedef struct s_square
{
	int				x;
	int				y;
	unsigned int	color;
	int				diff;
}	t_square;

typedef struct s_map
{
	char			*ligne;
	struct s_map	*next;
}	t_map;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_texture
{
	t_img	texture;
	int		width;
	int		height;
	char	*path;
}	t_texture;

typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
}	t_player;

typedef struct s_proj
{
	int			x;
	int			wall_height;
	int			start_pixel;
	int			end_pixel;
	char		*origin;
	char		*dst;
	double		proj_screen[4];
	double		dir_v[2];
	double		v[2];
	double		cur[2];
	double		prev[2];
	double		delta[2];
	double		percent_x;
	double		step;
	t_texture	target;
}	t_proj;

typedef struct s_info
{
	int				tabmap;
	void			*mlx;
	void			*win;
	int				width;
	int				height;
	t_img			img[NB_IMG];
	int				current_img;
	int				printerr;
	t_texture		no;
	t_texture		so;
	t_texture		we;
	t_texture		ea;
	int				f;
	int				c;
	int				isvalid;
	t_map			*lstmap;
	char			**map;
	char			dir;
	t_player		player;
	char			movement;
	int				xmax;
	int				ymax;
}	t_info;

int		charinstr(char *str, char c);
int		substrinstr(char *str, char *substr);
char	*getlaststr(char *ligne);
t_info	getinfo(t_map *map);
int		getlist(char *str);
char	**parsemap(t_map *lstmap);
void	freecharchar(char **lst);
void	puterr(char *str, t_info *info);
void	freelstmap(t_map *map);
int		mlx(t_info *info);
void	freeallchunk(t_map *map);
void	freeinfo(t_info *info);
int		loop(t_info *info);
void	raisewalls(t_info *info);
int		closewin(t_info *info);
int		iswall(t_info *info, double y, double x);
void	goforwardy(t_info *info);
void	goforwardx(t_info *info, double oldy);
void	goforward(t_info *info);
void	gobacky(t_info *info);
void	gobackx(t_info *info, double oldy);
void	goback(t_info *info);
void	golefty(t_info *info);
void	goleftx(t_info *info, double oldy);
void	goleft(t_info *info);
void	gorighty(t_info *info);
void	gorightx(t_info *info, double oldy);
void	goright(t_info *info);
void	turnright(t_info *info);
void	turnleft(t_info *info);
int		charinstr(char *str, char c);
int		substrinstr(char *str, char *substr);
char	*getlaststr(char *ligne);
int		getlist(char *str);
void	puterr(char *str, t_info *info);
void	freeallchunk(t_map *map);
void	freecharchar(char **lst);
void	freetexture(t_info *info);
void	freeinfo(t_info *info);
void	freelstmap(t_map *map);
int		checkcub(char **map, int i, int j);
void	infodir(t_info *info, char c, int i, int j);
void	dirmap(char **map, int i, int j, t_info *info);
void	checkcharmap(char **map, int i, int j, t_info *info);
int		isvalid(char **map, t_info *info);
int		ischr(char c);
void	printerrcoo(char *str, int i, int j, t_info *info);
void	initinfo(t_info *info);
int		lenof(t_map *lstmap);
int		ft_strlen_map(char *str);
int		check_view_integrity(t_info *info, double cur[2], double v[2], int hit);
void	get_walls(t_info *info, t_proj *proj);
int		draw_wall(t_info *info, t_proj *proj, int hit);
int		hook(int keycode, t_info *info);
int		hook_release(int keycode, t_info *info);
t_info	errdeligne(t_info info, t_map *current);

#endif
