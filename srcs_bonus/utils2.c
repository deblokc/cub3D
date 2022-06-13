/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdetune <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 11:19:30 by bdetune           #+#    #+#             */
/*   Updated: 2022/06/13 15:37:43 by bdetune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	distance(double x0, double y0, double x1, double y1)
{
	if (fabs(x1 - x0) < 0.0001)
		return (fabs(y1 - y0));
	if (fabs(y1 - y0) < 0.0001)
		return (fabs(x1 - x0));
	return (hypot(fabs(x1 - x0), fabs(y1 - y0)));
}

double	vector_angle(double v0[2], double v1[2])
{
	double	angle;

	angle = acos((v0[0] * v1[0] + v0[1] * v1[1]) \
			/ (distance(0, 0, v0[0], v0[1]) * distance(0, 0, v1[0], v1[1])));
	return (angle);
}

void	get_x_px_origin(t_proj *proj)
{
	if (proj->percent_x >= 1)
		proj->percent_x = 0.9999;
	proj->percent_x = floor(proj->percent_x \
					* (double)proj->target.texture[proj->target.numtext].width);
}
