/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:23:07 by tnaton            #+#    #+#             */
/*   Updated: 2022/06/09 17:56:07 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	turnleft(t_info *info)
{
	info->player.angle += ((5 * M_PI) / 180);
	if (info->player.angle == 0)
		info->player.angle = 2 * M_PI;
}

void	initinfo(t_info *info)
{
	info->no.path = NULL;
	info->so.path = NULL;
	info->we.path = NULL;
	info->ea.path = NULL;
	info->f = -1;
	info->c = -1;
	info->map = NULL;
	info->lstmap = NULL;
	info->dir = 0;
	info->printerr = 0;
	info->no.texture = NULL;
	info->so.texture = NULL;
	info->we.texture = NULL;
	info->ea.texture = NULL;
	info->door.texture = malloc(sizeof(t_img));
	info->door.texture->img = NULL;
	info->doors = NULL;
	info->mlx = NULL;
	info->win = NULL;
}

int	ischr(char c)
{
	return (c == '0' || c == '1' || c == 'E' \
			|| c == 'W' || c == 'N' || c == 'S' || c == '2');
}

int	lenof(t_map *lstmap)
{
	int	i;

	i = 0;
	while (lstmap)
	{
		lstmap = lstmap->next;
		i++;
	}
	return (i);
}

int	ft_strlen_map(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] != ' ' && str[i] != '\n')
		i++;
	return (i);
}
