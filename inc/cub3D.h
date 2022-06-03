/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:11:42 by tnaton            #+#    #+#             */
/*   Updated: 2022/06/03 16:05:32 by bdetune          ###   ########.fr       */
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
# include <sys/stat.h>
# include <fcntl.h>
# include "../libft/libft.h"

typedef struct s_map
{
	char			*ligne;
	struct s_map	*next;
}	t_map;

typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
}	t_player;

typedef struct s_info
{
	int				printerr;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	unsigned char	*f;
	unsigned char	*c;
	t_map			*lstmap;
	char			**map;
	char			dir;
	t_player		player;
}	t_info;

int				charinstr(char *str, char c);
int				substrinstr(char *str, char *substr);
char			*getlaststr(char *ligne);
t_info			getinfo(t_map *map);
unsigned char	*getlist(char *str);
char			**parsemap(t_map *lstmap);
void			freecharchar(char **lst);
void			puterr(char *str, t_info *info);

#endif
