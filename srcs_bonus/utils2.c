/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdetune <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 11:19:30 by bdetune           #+#    #+#             */
/*   Updated: 2022/06/11 11:19:51 by bdetune          ###   ########.fr       */
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
