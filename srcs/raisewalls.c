/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raisewalls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdetune <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:33:24 by bdetune           #+#    #+#             */
/*   Updated: 2022/06/01 19:16:10 by bdetune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_trace_vector(t_player player, double v[2]. double *x, double *y)
{
	if (!x || !y)
	{
		v[0] = info->player.angle + (M_PI / 4);
		v[1] = -sin(v[0]);
		v[0] = cos(v[0]);
		return ;
	}
}

void	first_edge(t_player player, double v[2], double delta[2], double cur[2])
{
	if (v[0] < 0)
	{
		cur[0] = floor(player.x) - 0.0001;
		delta[0] = fabs(player.x - cur[0]) / fabs(v[0]);
	}
	else if (v[0] > 0)
	{
		cur[0] = ceil(player.x);
		delta[0] = fabs(cur[0] - player.x) / fabs(v[0]);
	}
	else
		cur[0] = player.x;
	if (v[1] < 0)
	{
		cur[1] = floor(player.y) - 0.0001;
		delta[1] = fabs(player.y - cur[1]) / fabs(v[1]);
	}
	else if (v[1] > 0)
	{
		cur[1] = ceil(player.y);
		delta[1] = fabs(cur[1] - player.y) / fabs(v[1]);
	}
	else
		cur[1] = player.y;
}

void	get_next_edge(double v[2], double delta[2], double cur[2], int fixed)
{
	double	tmp[2];

	if (fixed == 0)
	{
		if (v[0] < 0)
			tmp[0] = cur[0] - 1;
		else
			tmp[0] = cur[0] + 1;
		delta[0] = fabs(tmp[0] - cur[0]) / fabs(v[0]);
		if (v[1] < 0)
			tmp[1] = floor(cur[1]) - 0.0001;
		else
			tmp[1] = ceil(cur[1]);
		delta[1] = fabs(tmp[1] - cur[1]) / fabs(v[1]);
	}
	else
	{
		if (v[1] < 0)
			tmp[1] = cur[1] - 1;
		else
			tmp[1] = cur[1] + 1;
		delta[1] = fabs(tmp[1] - cur[1]) / fabs(v[1]);
		if (v[0] < 0)
			tmp[0] = floor(cur[0]) - 0.0001;
		else
			tmp[0] = ceil(cur[0]);
		delta[0] = fabs(tmp[0] - cur[0]) / fabs(v[0]);
	}
	cur[0] = tmp[0];
	cur[1] = tmp[1];
}

int	straight_line(t_info *info, double cur[2], double v[2])
{
	if (!v[0])
	{
		if (info->map[(int)cur[1]][(int)cur[0]] == 1)
			return (draw_wall(info, cur, 1, v));
		else
		{
			if (v[1] < 0)
				cur[1] -= 1;
			else
				cur[1] += 1;
		}
	}
	else
	{
		if (info->map[(int)cur[1]][(int)cur[0]] == 1)
			return (draw_wall(info, cur, 2, v));
		else
		{
			if (v[0] < 0)
				cur[0] -= 1;
			else
				cur[0] += 1;
		}
	}
	return (0);
}

int	get_next_wall(t_info *info, double v[2], double delta[2], double cur[2])
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (!v[0] || !v[1])
			hit = straight_line(info, cur, v);
		else
		{
			if (delta[0] < delta[1])
			{
				cur[1] = (fabs(cur[0] - info->player.x) / v[0]) * v[1] + player.y;
				if (info->map[(int)cur[1]][(int)cur[0]] == 1)
				{
					hit = 2;
					draw_wall(info, cur, hit, v);
				}
				else
					get_next_edge(v, delta, cur, 0);
			}
			else
			{
				cur[0] = (fabs(cur[1] - info->player.y) / v[1]) * v[0] + player.x;
				if (info->map[(int)cur[1]][(int)cur[0]] == 1)
				{
					hit = 1;
					draw_wall(info, cur, hit, v);
				}
				else
					get_next_edge(v, delta, cur, 1);
			}
		}
	}
}

void	raisewalls(t_info *info)
{
	double	v[2];
	double	delta[2];
	double	cur[2];
	int		hit;
	int		end;

	get_trace_vector(info->player, v, NULL, NULL);
	first_edge(info->player, v, delta, cur);
	end = 0;
	while (!end)
		end = get_next_wall(info, v, delta, cur)
}
