#include "cub3D.h"

static int	check_north(t_info *info, double cur[2], double v[2])
{
	int	hit;

	hit = 1;
	if (info->map[(int)(cur[1] + 1)][(int)(cur[0])] == '1')
	{
		hit = 2;
		if ((v[0] <= 0
				&& info->map[(int)(cur[1])][(int)(cur[0] + 1)] == '1')
			|| (v[0] >= 0
				&& info->map[(int)(cur[1])][(int)(cur[0] - 1)] == '1'))
		{
			hit = 1;
			if (v[0] <= 0)
				cur[0] = 0;
			else
				cur[0] = 0.9999;
			cur[1] = 0.9999;
		}
	}
	return (hit);
}

static int	check_south(t_info *info, double cur[2], double v[2])
{
	int	hit;

	hit = 1;
	if (info->map[(int)(cur[1] - 1)][(int)(cur[0])] == '1')
	{
		hit = 2;
		if ((v[0] <= 0
				&& info->map[(int)(cur[1])][(int)(cur[0] + 1)] == '1')
			|| (v[0] >= 0
				&& info->map[(int)(cur[1])][(int)(cur[0] - 1)] == '1'))
		{
			hit = 1;
			if (v[0] <= 0)
				cur[0] = 0;
			else
				cur[0] = 0.9999;
			cur[1] = 0;
		}
	}
	return (hit);
}

static int	check_west(t_info *info, double cur[2], double v[2])
{
	int	hit;

	hit = 2;
	if (info->map[(int)(cur[1])][(int)(cur[0] + 1)] == '1')
	{
		hit = 1;
		if ((v[1] <= 0
				&& info->map[(int)(cur[1] + 1)][(int)(cur[0])] == '1')
			|| (v[1] >= 0
				&& info->map[(int)(cur[1] - 1)][(int)(cur[0])] == '1'))
		{
			hit = 2;
			if (v[1] <= 0)
				cur[1] = 0;
			else
				cur[1] = 0.9999;
			cur[0] = 0.9999;
		}
	}
	return (hit);
}

static int	check_east(t_info *info, double cur[2], double v[2])
{
	int	hit;

	hit = 2;
	if (info->map[(int)(cur[1])][(int)(cur[0] - 1)] == '1')
	{
		hit = 1;
		if ((v[1] <= 0
				&& info->map[(int)(cur[1] + 1)][(int)(cur[0])] == '1')
			|| (v[1] >= 0
				&& info->map[(int)(cur[1] - 1)][(int)(cur[0])] == '1'))
		{
			hit = 2;
			if (v[1] <= 0)
				cur[1] = 0;
			else
				cur[1] = 0.9999;
			cur[0] = 0;
		}
	}
	return (hit);
}

int	check_view_integrity(t_info *info, double cur[2], double v[2], int hit)
{
	if (hit == 1)
	{
		if (v[1] < 0)
			hit = check_north(info, cur, v);
		else
			hit = check_south(info, cur, v);
	}
	else
	{
		if (v[0] < 0)
			hit = check_west(info, cur, v);
		else
			hit = check_east(info, cur, v);
	}
	return (hit);
}
