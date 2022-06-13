/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdetune <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:06:22 by bdetune           #+#    #+#             */
/*   Updated: 2022/06/13 13:41:33 by bdetune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	add_door(t_info *info, int y, int x)
{
	t_door	*current;
	t_door	*new_door;

	new_door = (t_door *)ft_calloc(1, sizeof(t_door));
	if (!new_door)
	{
		freeinfo(info);
		perror("Malloc error");
		exit(1);
	}
	new_door->x = x;
	new_door->y = y;
	new_door->opened_time = 0;
	new_door->visible = 100;
	new_door->motion = 0;
	if (!info->doors)
		info->doors = new_door;
	else
	{
		current = info->doors;
		while (current->next)
			current = current->next;
		current->next = new_door;
	}
}

int	add_door_text(t_info *info)
{
	if (!info->door.path)
		info->door.path = DOOR_PATH;
	info->door.numtext = 0;
	info->door.texture[info->door.numtext].img = \
			mlx_xpm_file_to_image(info->mlx, info->door.path, \
			&info->door.texture[info->door.numtext].width, \
			&info->door.texture[info->door.numtext].height);
	if (!info->door.texture[info->door.numtext].img)
		return (puterr("Impossible d'ouvrir ", info), \
				ft_putstr_fd(DOOR_PATH, 2), ft_putstr_fd(" !\n", 2), 1);
	info->door.texture->addr = mlx_get_data_addr(info->door.texture->img, \
			&info->door.texture->bits_per_pixel, \
			&info->door.texture->line_length, &info->door.texture->endian);
	return (0);
}

t_door	*find_door(t_info *info, int coords[2])
{
	t_door	*current;

	current = info->doors;
	while (current)
	{
		if (current->x == coords[0] && current->y == coords[1])
			return (current);
		current = current->next;
	}
	return (NULL);
}
