/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:11:42 by tnaton            #+#    #+#             */
/*   Updated: 2022/06/01 13:32:14 by bdetune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
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
	int		x;
	int		y;
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
