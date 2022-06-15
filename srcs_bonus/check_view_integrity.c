/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_view_integrity.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdetune <bdetune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 09:43:04 by bdetune           #+#    #+#             */
/*   Updated: 2022/06/15 13:24:29 by bdetune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	check_north(t_info *info, t_proj *proj)
{
	double	tmp[2];

	tmp[0] = proj->cur[0];
	tmp[1] = proj->cur[1];
	if (info->map[(int)(tmp[1] + 1)][(int)(tmp[0])] == '1')
	{
		if (check_north_corner(info, proj, tmp))
			return (1);
		return (set_current(proj->cur, tmp[0], ceil(tmp[1])), 2);
	}
	else if (fabs(ceil(tmp[0]) - tmp[0]) < 0.0002
		|| fabs(floor(tmp[0]) - tmp[0]) < 0.0001)
	{
		set_current(proj->cur, tmp[0], ceil(tmp[1]));
		if (is_on_door(info, proj, 2))
		{
			if (check_north_corner(info, proj, tmp))
				return (1);
			return (set_current(proj->cur, tmp[0], ceil(tmp[1])), \
					is_on_door(info, proj, 2), 2);
		}
	}
	return (set_current(proj->cur, tmp[0], tmp[1]), 1);
}

static int	check_south(t_info *info, t_proj *proj)
{
	double	tmp[2];

	tmp[0] = proj->cur[0];
	tmp[1] = proj->cur[1];
	if (info->map[(int)(tmp[1] - 1)][(int)(tmp[0])] == '1')
	{
		if ((proj->v[0] <= 0
				&& info->map[(int)(tmp[1])][(int)(tmp[0] + 1)] == '1')
			|| (proj->v[0] >= 0
				&& info->map[(int)(tmp[1])][(int)(tmp[0] - 1)] == '1'))
		{
			if (proj->v[0] <= 0)
				proj->cur[0] = 0;
			else
				proj->cur[0] = 0.9999;
			proj->cur[1] = 0;
			return (1);
		}
		else
		{
			if (proj->v[0] <= 0)
			{
				proj->cur[0] = floor(tmp[0] + 1);
				proj->cur[1] = tmp[1];
				if (is_on_door(info, proj, 1))
					return (1);
			}
			else
			{
				proj->cur[0] = floor(tmp[0]) - 0.0001;
				proj->cur[1] = tmp[1];
				if (is_on_door(info, proj, 1))
					return (1);
			}
		}
		proj->cur[0] = tmp[0];
		proj->cur[1] = floor(tmp[1]) - 0.0001;
		return (2);
	}
	else if (fabs(ceil(tmp[0]) - tmp[0]) < 0.0002
		|| fabs(floor(tmp[0]) - tmp[0]) < 0.0001)
	{
		proj->cur[0] = tmp[0];
		proj->cur[1] = floor(tmp[1]) - 0.0001;
		if (is_on_door(info, proj, 2))
		{
			if ((proj->v[0] <= 0
					&& info->map[(int)(tmp[1])][(int)(tmp[0] + 1)] == '1')
				|| (proj->v[0] >= 0
					&& info->map[(int)(tmp[1])][(int)(tmp[0] - 1)] == '1'))
			{
				if (proj->v[0] <= 0)
					proj->cur[0] = 0;
				else
					proj->cur[0] = 0.9999;
				proj->cur[1] = 0;
				return (1);
			}
			else
			{
				if (proj->v[0] <= 0)
				{
					proj->cur[0] = floor(tmp[0] + 1);
					proj->cur[1] = tmp[1];
					if (is_on_door(info, proj, 1))
						return (1);
				}
				else
				{
					proj->cur[0] = floor(tmp[0]) - 0.0001;
					proj->cur[1] = tmp[1];
					if (is_on_door(info, proj, 1))
						return (1);
				}
			}
			proj->cur[0] = tmp[0];
			proj->cur[1] = floor(tmp[1]) - 0.0001;
			is_on_door(info, proj, 2);
			return (2);
		}
	}
	proj->cur[0] = tmp[0];
	proj->cur[1] = tmp[1];
	return (1);
}

static int	check_west(t_info *info, t_proj *proj)
{
	double	tmp[2];

	tmp[0] = proj->cur[0];
	tmp[1] = proj->cur[1];
	if (info->map[(int)(tmp[1])][(int)(tmp[0] + 1)] == '1')
	{
		if ((proj->v[1] <= 0
				&& info->map[(int)(tmp[1] + 1)][(int)(tmp[0])] == '1')
			|| (proj->v[1] >= 0
				&& info->map[(int)(tmp[1] - 1)][(int)(tmp[0])] == '1'))
		{
			if (proj->v[1] <= 0)
				proj->cur[1] = 0;
			else
				proj->cur[1] = 0.9999;
			proj->cur[0] = 0.9999;
			return (2);
		}
		else
		{
			if (proj->v[1] <= 0)
			{
				proj->cur[0] = tmp[0];
				proj->cur[1] = floor(tmp[1] + 1);
				if (is_on_door(info, proj, 2))
					return (2);
			}
			else
			{
				proj->cur[0] = tmp[0];
				proj->cur[1] = floor(tmp[1]) - 0.0001;
				if (is_on_door(info, proj, 2))
					return (2);
			}
		}
		proj->cur[0] = ceil(tmp[0]);
		proj->cur[1] = tmp[1];
		return (1);
	}
	else if (fabs(ceil(tmp[1]) - tmp[1]) < 0.0002
		|| fabs(floor(tmp[1]) - tmp[1]) < 0.0001)
	{
		proj->cur[0] = ceil(tmp[0]);
		proj->cur[1] = tmp[1];
		if (is_on_door(info, proj, 1))
		{
			if ((proj->v[1] <= 0
					&& info->map[(int)(tmp[1] + 1)][(int)(tmp[0])] == '1')
				|| (proj->v[1] >= 0
					&& info->map[(int)(tmp[1] - 1)][(int)(tmp[0])] == '1'))
			{
				if (proj->v[1] <= 0)
					proj->cur[1] = 0;
				else
					proj->cur[1] = 0.9999;
				proj->cur[0] = 0.9999;
				return (2);
			}
			else
			{
				if (proj->v[1] <= 0)
				{
					proj->cur[0] = tmp[0];
					proj->cur[1] = floor(tmp[1] + 1);
					if (is_on_door(info, proj, 2))
						return (2);
				}
				else
				{
					proj->cur[0] = tmp[0];
					proj->cur[1] = floor(tmp[1]) - 0.0001;
					if (is_on_door(info, proj, 2))
						return (2);
				}
			}
			proj->cur[0] = ceil(tmp[0]);
			proj->cur[1] = tmp[1];
			is_on_door(info, proj, 1);
			return (1);
		}
	}
	proj->cur[0] = tmp[0];
	proj->cur[1] = tmp[1];
	return (2);
}

static int	check_east(t_info *info, t_proj *proj)
{
	double	tmp[2];

	tmp[0] = proj->cur[0];
	tmp[1] = proj->cur[1];
	if (info->map[(int)(tmp[1])][(int)(tmp[0] - 1)] == '1')
	{
		if ((proj->v[1] <= 0
				&& info->map[(int)(tmp[1] + 1)][(int)(tmp[0])] == '1')
			|| (proj->v[1] >= 0
				&& info->map[(int)(tmp[1] - 1)][(int)(tmp[0])] == '1'))
		{
			if (proj->v[1] <= 0)
				proj->cur[1] = 0;
			else
				proj->cur[1] = 0.9999;
			proj->cur[0] = 0;
			return (2);
		}
		else
		{
			if (proj->v[1] <= 0)
			{
				proj->cur[0] = tmp[0];
				proj->cur[1] = floor(tmp[1] + 1);
				if (is_on_door(info, proj, 2))
					return (2);
			}
			else
			{
				proj->cur[0] = tmp[0];
				proj->cur[1] = floor(tmp[1]) - 0.0001;
				if (is_on_door(info, proj, 2))
					return (2);
			}
		}
		proj->cur[0] = floor(tmp[0]) - 0.0001;
		proj->cur[1] = tmp[1];
		return (1);
	}
	else if (fabs(ceil(tmp[1]) - tmp[1]) < 0.0002
		|| fabs(floor(tmp[1]) - tmp[1]) < 0.0001)
	{
		proj->cur[0] = floor(tmp[0]) - 0.0001;
		proj->cur[1] = tmp[1];
		if (is_on_door(info, proj, 1))
		{
			if ((proj->v[1] <= 0
					&& info->map[(int)(tmp[1] + 1)][(int)(tmp[0])] == '1')
				|| (proj->v[1] >= 0
					&& info->map[(int)(tmp[1] - 1)][(int)(tmp[0])] == '1'))
			{
				if (proj->v[1] <= 0)
					proj->cur[1] = 0;
				else
					proj->cur[1] = 0.9999;
				proj->cur[0] = 0;
				return (2);
			}
			else
			{
				if (proj->v[1] <= 0)
				{
					proj->cur[0] = tmp[0];
					proj->cur[1] = floor(tmp[1] + 1);
					if (is_on_door(info, proj, 2))
						return (2);
				}
				else
				{
					proj->cur[0] = tmp[0];
					proj->cur[1] = floor(tmp[1]) - 0.0001;
					if (is_on_door(info, proj, 2))
						return (2);
				}
			}
			proj->cur[0] = floor(tmp[0]) - 0.0001;
			proj->cur[1] = tmp[1];
			is_on_door(info, proj, 1);
			return (1);
		}
	}
	proj->cur[0] = tmp[0];
	proj->cur[1] = tmp[1];
	return (2);
}

int	check_view_integrity(t_info *info, t_proj *proj, int hit)
{
	if (hit == 1)
	{
		if (proj->v[1] < 0)
			hit = check_north(info, proj);
		else
			hit = check_south(info, proj);
	}
	else
	{
		if (proj->v[0] < 0)
			hit = check_west(info, proj);
		else
			hit = check_east(info, proj);
	}
	return (hit);
}
