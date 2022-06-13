/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdetune <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 12:47:11 by bdetune           #+#    #+#             */
/*   Updated: 2022/06/13 12:47:38 by bdetune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	hook(int keycode, t_info *info)
{
	if (keycode == 65307)
		closewin(info);
	if (keycode == 119)
		info->movement += 1;
	if (keycode == 115)
		info->movement += (1 << 1);
	if (keycode == 97)
		info->movement += (1 << 2);
	if (keycode == 100)
		info->movement += (1 << 3);
	if (keycode == 65363)
		info->movement += (1 << 4);
	if (keycode == 65361)
		info->movement += (1 << 5);
	loop(info);
	return (0);
}

int	hook_release(int keycode, t_info *info)
{
	if (keycode == 119)
		info->movement -= 1;
	if (keycode == 115)
		info->movement -= (1 << 1);
	if (keycode == 97)
		info->movement -= (1 << 2);
	if (keycode == 100)
		info->movement -= (1 << 3);
	if (keycode == 65363)
		info->movement -= (1 << 4);
	if (keycode == 65361)
		info->movement -= (1 << 5);
	loop(info);
	return (0);
}
