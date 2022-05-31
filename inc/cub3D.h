/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:11:42 by tnaton            #+#    #+#             */
/*   Updated: 2022/05/31 15:51:54 by tnaton           ###   ########.fr       */
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

typedef struct s_info
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	unsigned char	*f;
	unsigned char	*c;
	t_map			*lstmap;
	char			**map;
	char			dir;
}	t_info;

int				charinstr(char *str, char c);
int				substrinstr(char *str, char *substr);
char			*getlaststr(char *ligne);
t_info			getinfo(t_map *map);
unsigned char	*getlist(char *str);
char			**parsemap(t_map *lstmap);
void			freecharchar(char **lst);

#endif
