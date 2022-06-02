/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raisewalls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdetune <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:33:24 by bdetune           #+#    #+#             */
/*   Updated: 2022/06/02 14:43:36 by bdetune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_trace_vector(t_player player, double v[2], double *x, double *y)
{
	if (!x || !y)
	{
		v[0] = player.angle + (M_PI / 4);
		v[1] = -sin(v[0]);
		v[0] = cos(v[0]);
		printf("player x: %.4f, player y: %.4f\n", player.x, player.y);
		printf("x dir: %.4f, y dir: %.4f\n", v[0], v[1]);
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

	printf("fixed value: %d\n", fixed);
	if (fixed == 0)
	{
		if (v[0] < 0)
			tmp[0] = cur[0] - 1;
		else
			tmp[0] = cur[0] + 1;
		delta[0] = fabs(tmp[0] - cur[0]) / fabs(v[0]);
		if (v[1] < 0)
		{
			printf("val before floor: %.4f\n", cur[1]);
			tmp[1] = floor(cur[1]) - 0.0001;
			printf("val after floor: %.4f\n", tmp[1]);
		}
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
		{
			printf("val before floor: %.4f\n", cur[0]);
			tmp[0] = floor(cur[0]) - 0.0001;
			printf("val after floor: %.4f\n", tmp[0]);
		}
		else
			tmp[0] = ceil(cur[0]);
		delta[0] = fabs(tmp[0] - cur[0]) / fabs(v[0]);
	}
	cur[0] = tmp[0];
	cur[1] = tmp[1];
	printf("out val: %.4f, %.4f\n", cur[0], cur[1]);
}

int	draw_first_wall(t_info *info, double cur[2], int hit, double v[2])
{
	double	distance0;
	double	angle;
	double	central_vector[0];
	double	end[2];

	distance0 = hypot(fabs(cur[0] - info->player.x), fabs(cur[1] - info->player.y)) * cos((M_PI / 4));
	central_vector[0] = cos(info->player.angle);
	central_vector[1] = -sin(info->player.angle);
	printf("found intersection at %.4f; %.4f\n", cur[0], cur[1]);
	printf("Hit on %c\n", hit==1?'y':'x');
	printf("Distance to projection plane: %.8f\n", distance0);
	if (hit == 1)
	{
		if (v[1] < 0)
			end[0] = ceil(cur[0]) - 0.0001;
		else
			end[0] = floor(cur[0]);
		end[1] = cur[1];
	}
	else
	{
		if (v[0] < 0)
			end[1] = floor(cur[1]);
		else
			end[1] = ceil(cur[1]) - 0.0001;
		end[0] = cur[0];
	}
	printf("End point of block at %.4f; %.4f\n", end[0], end[1]);
	return (hit);
}

int	straight_line(t_info *info, double cur[2], double v[2])
{
	if (!v[0])
	{
		if (info->map[(int)cur[1]][(int)cur[0]] == '1')
			return (draw_first_wall(info, cur, 1, v));
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
		if (info->map[(int)cur[1]][(int)cur[0]] == '1')
			return (draw_first_wall(info, cur, 2, v));
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

int	get_walls(t_info *info, double v[2], double delta[2], double cur[2])
{
	double	prev[2];
	int		hit;

	hit = 0;
	prev[0] = info->player.x;
	prev[1] = info->player.y;
	while (!hit)
	{
		if (!v[0] || !v[1])
			hit = straight_line(info, cur, v);
		else
		{
			if (delta[0] < delta[1])
			{
				cur[1] = delta[0] * v[1] + prev[1];
				printf("current x: %.4f, current y: %.4f\n", cur[0], cur[1]);
				if (info->map[(int)cur[1]][(int)cur[0]] == '1')
					hit = draw_first_wall(info, cur, 2, v);
				else
				{
					prev[0] = cur[0];
					prev[1] = cur[1];
					get_next_edge(v, delta, cur, 0);
				}
			}
			else
			{
				cur[0] = delta[1] * v[0] + prev[0];
				printf("current x: %.4f, current y: %.4f\n", cur[0], cur[1]);
				if (info->map[(int)cur[1]][(int)cur[0]] == '1')
					hit = draw_first_wall(info, cur, 1, v);
				else
				{
					prev[0] = cur[0];
					prev[1] = cur[1];
					get_next_edge(v, delta, cur, 1);
				}
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

	get_trace_vector(info->player, v, NULL, NULL);
	first_edge(info->player, v, delta, cur);
	get_walls(info, v, delta, cur);
}

int main()
{
	int		i;
	t_info	info;

	info.map = calloc(6, sizeof(char *));
	i = 0;
	while (i < 5)
	{
		info.map[i] = calloc(6, sizeof(char));
		i++;
	}
	info.map[0][0] = '1';
	info.map[0][1] = '1';
	info.map[0][2] = '1';
	info.map[0][3] = '1';
	info.map[0][4] = '1';
	info.map[1][0] = '1';
	info.map[1][4] = '1';
	info.map[2][0] = '1';
	info.map[2][4] = '1';
	info.map[3][0] = '1';
	info.map[3][4] = '1';
	info.map[4][0] = '1';
	info.map[4][1] = '1';
	info.map[4][2] = '1';
	info.map[4][3] = '1';
	info.map[4][4] = '1';
	info.player.angle = M_PI / 2;
	info.player.x = 1.5;
	info.player.y = 1.5;
	raisewalls(&info);
	return (0);
}
