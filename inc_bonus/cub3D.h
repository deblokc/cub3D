/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:11:42 by tnaton            #+#    #+#             */
/*   Updated: 2022/06/15 14:48:13 by bdetune          ###   ########.fr       */
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
# include <sys/types.h>
# include <dirent.h>
# include <time.h>
# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# define WIDTH 2500
# define HEIGHT 1300
# define NB_IMG 16
# define STEP 0.25
# define DOOR_PATH "textures/door.xpm"
# define EXIT_PATH "textures/portal/"
# define END_PATH "textures/theend.xpm"

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
	int		width;
	int		height;
}	t_img;

typedef struct s_texture
{
	t_img	*texture;
	int		numtext;
	int		numtextmax;
	char	*path;
}	t_texture;

typedef struct s_door
{
	int				x;
	int				y;
	char			motion;
	char			visible;
	char			opened_time;
	struct s_door	*next;
}	t_door;

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
	int			exit_st_px;
	int			exit_end_px;
	char		*origin;
	char		*dst;
	char		is_door;
	char		has_exit;
	double		proj_screen[4];
	double		dir_v[2];
	double		v[2];
	double		cur[2];
	double		prev[2];
	double		delta[2];
	double		percent_x;
	double		step;
	double		exit_distance;
	double		exit_v[2];
	double		exit_height;
	double		exit_center[2];
	double		exit_ends[4];
	double		exit_percent_x;
	double		exit_step;
	t_door		*door;
	t_texture	target;
}	t_proj;

typedef struct s_info
{
	int				asended;
	int				tabmap;
	void			*mlx;
	void			*win;
	int				height;
	int				width;
	t_img			img[NB_IMG];
	int				current_img;
	int				printerr;
	t_texture		no;
	t_texture		so;
	t_texture		we;
	t_texture		ea;
	t_texture		door;
	t_texture		exit;
	t_texture		end;
	t_door			*doors;
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
	int				click;
	int				xmouse;
	int				newxmouse;
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
int		check_view_integrity(t_info *info, t_proj *proj, int hit);
void	get_walls(t_info *info, t_proj *proj);
int		draw_wall(t_info *info, t_proj *proj, int hit);
void	add_door(t_info *info, int y, int x);
int		add_door_text(t_info *info);
int		is_on_door(t_info *info, t_proj *proj, int hit);
t_door	*find_door(t_info *info, int coords[2]);
t_map	*newchunk(char *str);
double	distance(double x0, double y0, double x1, double y1);
double	vector_angle(double v0[2], double v1[2]);
void	handle_exit(t_info *info, t_proj *proj);
void	draw_exit(t_info *info, t_proj *proj);
int		set_door_texture(t_info *info, t_proj *proj, int vect);
void	get_x_px_origin(t_proj *proj);
void	freetexture(t_info *info);
void	freetext(t_texture *text, void *mlx);
void	freedoors(t_info *info);
int		isfloor(char c);
void	freetexture(t_info *info);
void	freedoors(t_info *info);
void	dirmap(char **map, int i, int j, t_info *info);
int		isfloor(char c);
void	hook_list(t_info *info);
int		mouse_move(int x, int y, t_info *info);
int		mouse_release(int keycode, int x, int y, t_info *info);
int		mouse_press(int keycode, int x, int y, t_info *info);
int		hook_release(int keycode, t_info *info);
int		hook(int keycode, t_info *info);
void	handle_doors(t_info *info);
void	toggle_door(t_info *info);
void	putminimap(t_info *info, t_img *img);
void	putmaptoimg(t_info *info, t_img *img);
void	putmaptoimg2(t_info *info, int lst[2], char c, int diff);
void	putsquare(t_info *info, t_img *img, int lst[3], unsigned int color);
void	putplayer(t_info *info, t_img *img, int coords[2], unsigned int color);
int		get_text(t_texture *text, t_info *info);
int		gettextdir(t_texture *text, t_info *info, DIR *dir);
void	initgettextdir(t_texture *text, DIR *dir, int *i);
int		gettextdirerr(t_texture *text, t_info *info, DIR *dir, int i);
int		gettextnodir(t_texture *text, t_info *info);
void	putpixel(t_img *img, int x, int y, unsigned int color);
int		getdiff(t_info *info);
void	set_current(double cur[2], double x, double y);
int		check_north_corner(t_info *info, t_proj *proj, double tmp[2]);
int		check_south_corner(t_info *info, t_proj *proj, double tmp[2]);
int		check_west_corner(t_info *info, t_proj *proj, double tmp[2]);
int		check_east_corner(t_info *info, t_proj *proj, double tmp[2]);

#endif
