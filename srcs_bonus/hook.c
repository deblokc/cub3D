/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 19:03:10 by tnaton            #+#    #+#             */
/*   Updated: 2022/06/13 19:04:17 by tnaton           ###   ########.fr       */
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
	if (keycode == 65289)
		info->tabmap = 1;
	if (keycode == 32)
		toggle_door(info);
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
	if (keycode == 65289)
		info->tabmap = 0;
	loop(info);
	return (0);
}

int	mouse_press(int keycode, int x, int y, t_info *info)
{
	(void)y;
	if (keycode == 1)
	{
		info->newxmouse = x;
		info->xmouse = x;
		info->click = 1;
	}
	return (0);
}

int	mouse_release(int keycode, int x, int y, t_info *info)
{
	(void)y;
	if (keycode == 1)
	{
		info->xmouse = x;
		info->click = 0;
	}
	return (info->tabmap);
}

int	mouse_move(int x, int y, t_info *info)
{
	(void)y;
	if (info->click)
		info->newxmouse = x;
	else
		info->xmouse = x;
	return (info->tabmap);
}
