/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_view_integrity_corners.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdetune <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:22:15 by bdetune           #+#    #+#             */
/*   Updated: 2022/06/15 13:25:38 by bdetune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_north_corner(t_info *info, t_proj *proj, double tmp[2])
{
	if ((proj->v[0] <= 0 && info->map[(int)(tmp[1])][(int)(tmp[0] + 1)] == '1')
		|| (proj->v[0] >= 0
			&& info->map[(int)(tmp[1])][(int)(tmp[0] - 1)] == '1'))
	{
		proj->cur[0] = 0.9999;
		if (proj->v[0] <= 0)
			proj->cur[0] = 0;
		proj->cur[1] = 0.9999;
		return (1);
	}
	if (proj->v[0] <= 0)
	{
		proj->cur[1] = tmp[1];
		proj->cur[0] = floor(tmp[0] + 1);
		if (is_on_door(info, proj, 1))
			return (1);
	}
	else
	{
		proj->cur[1] = tmp[1];
		proj->cur[0] = floor(tmp[0]) - 0.0001;
		if (is_on_door(info, proj, 1))
			return (1);
	}
	return (0);
}
