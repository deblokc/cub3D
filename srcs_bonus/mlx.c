/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:39:50 by tnaton            #+#    #+#             */
/*   Updated: 2022/06/13 18:37:59 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	getdiff(t_info *info)
{
	int	x;
	int	y;
	int	max;

	y = 0;
	x = 0;
	max = WIDTH;
	if (max > HEIGHT)
		max = HEIGHT;
	if (max / (info->xmax) > max / (info->ymax))
		return (max / (info->ymax));
	return (max / (info->xmax));
}

void	putpixel(t_img *img, int x, int y, unsigned int color)
{
	char	*dest;

	dest = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dest = color;
}

void	putplayer(t_img *img, int x, int y, unsigned int color)
{
	int	nexty;
	int	nextx;
	int	rety;
	int	retx;

	retx = x - 3;
	rety = y;
	nexty = y + 3;
	nextx = x + 3;
	y -= 3;
	while (y < nexty)
	{
		x = retx;
		while (x < nextx)
		{
			if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
				putpixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	putsquare(t_img *img, int lst[2], unsigned int color, int diff)
{
	int		nexty;
	int		nextx;
	int		retx;
	int		rety;

	retx = lst[0];
	rety = lst[1];
	nexty = lst[1] + diff;
	nextx = lst[0] + diff;
	while (lst[1] < nexty)
	{
		lst[0] = retx;
		while (lst[0] < nextx)
		{
			if (lst[0] >= 0 && lst[0] < WIDTH && lst[1] >= 0 && lst[1] < HEIGHT)
				putpixel(img, lst[0], lst[1], color);
			lst[0]++;
		}
		lst[1]++;
	}
	lst[0] = retx;
	lst[1] = rety;
}

void	putmaptoimg2(t_info *info, int lst[2], char c, int diff)
{
	if (c == '2')
		putsquare(&info->img[info->current_img], lst, 0x00FFFF, diff);
	if (c == '1')
		putsquare(&info->img[info->current_img], lst, 0xFFFFFF, diff);
	if (c == '0' || c == 'X')
		putsquare(&info->img[info->current_img], lst, 0x0000FF, diff);
	if (c == 'N' || c == 'W' || c == 'E' || c == 'S')
		putsquare(&info->img[info->current_img], lst, 0x00FF00, diff);
}

void	putmaptoimg(t_info *info, t_img *img)
{
	int	xmap;
	int	ymap;
	int	lst[2];
	int	diff;

	diff = getdiff(info);
	ymap = 0;
	lst[1] = 0;
	while (info->map[ymap])
	{
		xmap = 0;
		lst[0] = 0;
		while (info->map[ymap][xmap])
		{
			putmaptoimg2(info, lst, info->map[ymap][xmap], diff);
			lst[0] += diff;
			xmap++;
		}
		lst[1] += diff;
		ymap++;
	}
	putplayer(img, diff * info->player.x, diff * info->player.y, 0xFF0000);
}

void	putminimap(t_info *info, t_img *img)
{
	int	x;
	int	y;
	int	lst[2];

	lst[1] = 0;
	y = (int)info->player.y - 2;
	while (y < (int)info->player.y + 3)
	{
		lst[0] = 0;
		x = (int)info->player.x - 2;
		while (x < (int)info->player.x + 3)
		{
			if (x >= 0 && y >= 0 && x < info->xmax && y < info->ymax)
				putmaptoimg2(info, lst, info->map[y][x], 25);
			lst[0] += 25;
			x++;
		}
		lst[1] += 25;
		y++;
	}
	putplayer(img, 50 + (25 * (info->player.x - floor(info->player.x))), \
			50 + (25 * (info->player.y - floor(info->player.y))), 0xFF0000);
}

void	toggle_door(t_info *info)
{
	t_proj	proj;
	int		coords[2];

	proj.door = NULL;
	proj.v[0] = cos(info->player.angle);
	proj.v[1] = -sin(info->player.angle);
	proj.cur[0] = info->player.x;
	proj.delta[0] = 10;
	if (proj.v[0] < -0.0001 || proj.v[0] > 0.0001)
	{
		if (proj.v[0] < -0.0001)
			proj.cur[0] = floor(info->player.x) - 0.0001;
		else
			proj.cur[0] = ceil(info->player.x);
		proj.delta[0] = fabs(proj.cur[0] - info->player.x) / fabs(proj.v[0]);
	}
	proj.cur[1] = info->player.y;
	proj.delta[1] = 10;
	if (proj.v[1] < -0.0001 || proj.v[1] > 0.0001)
	{
		if (proj.v[1] < -0.0001)
			proj.cur[1] = floor(info->player.y) - 0.0001;
		else
			proj.cur[1] = ceil(info->player.y);
		proj.delta[1] = fabs(proj.cur[1] - info->player.y) / fabs(proj.v[1]);
	}
	if (proj.delta[0] < proj.delta[1])
		proj.cur[1] = proj.delta[0] * proj.v[1] + info->player.y;
	else
		proj.cur[0] = proj.delta[1] * proj.v[0] + info->player.x;
	while (distance(proj.cur[0], proj.cur[1], \
				info->player.x, info->player.y) <= 1)
	{
		coords[0] = (int)proj.cur[0];
		coords[1] = (int)proj.cur[1];
		if (info->map[coords[1]][coords[0]] == '1')
			return ;
		if (info->map[coords[1]][coords[0]] == '2')
		{
			proj.door = find_door(info, coords);
			break ;
		}
		proj.cur[0] += 0.1 * proj.v[0];
		proj.cur[1] += 0.1 * proj.v[1];
	}
	if (proj.door)
	{
		proj.door->opened_time = 0;
		if (proj.door->motion == 0 && proj.door->visible == 100)
			proj.door->motion = -1;
		else if (proj.door->motion == 0 && proj.door->visible == 0)
			proj.door->motion = 1;
		else if (proj.door->motion == 1)
			proj.door->motion = -1;
		else
			proj.door->motion = 1;
	}
}

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

int	gettextnodir(t_texture *text, t_info *info)
{
	text->numtextmax = 1;
	text->texture = malloc(sizeof(t_img) * 2);
	text->texture[0].img = mlx_xpm_file_to_image(info->mlx, text->path, \
			&text->texture[0].width, &text->texture[0].height);
	if (!text->texture[0].img)
	{
		free(text->texture);
		text->texture = NULL;
		return (puterr("Impossible d'ouvrir ", info), \
				ft_putstr_fd(text->path, 2), ft_putstr_fd(" !\n", 2), 1);
	}
	text->texture[0].addr = mlx_get_data_addr(text->texture[0].img, \
			&text->texture[0].bits_per_pixel, &text->texture[0].line_length,
			&text->texture[0].endian);
	return (0);
}

int	gettextdirerr(t_texture *text, t_info *info, DIR *dir, char *tmp)
{
	closedir(dir);
	free(text->texture);
	free(tmp);
	text->texture = NULL;
	return (puterr("Impossible d'ouvrir ", info), \
		ft_putstr_fd(text->path, 2), ft_putstr_fd(" !\n", 2), 1);
}

void	initgettextdir(t_texture *text, DIR *dir, int *i)
{
	struct dirent	*file;

	*i = 0;
	file = readdir(dir);
	while (file != NULL)
	{
		*(i) += 1;
		file = readdir(dir);
	}
	*(i) -= 2;
	text->texture = malloc(sizeof(t_img) * (*(i) + 1));
	text->numtextmax = *(i);
}

int	gettextdir(t_texture *text, t_info *info, DIR *dir)
{
	char			*tmp;
	int				i;

	initgettextdir(text, dir, &i);
	while (i--)
	{
		tmp = ft_strjoin_free(ft_strdup(text->path), ft_itoa(i));
		text->texture[i].img = mlx_xpm_file_to_image(info->mlx, tmp, \
				&text->texture[i].width, &text->texture[i].height);
		if (!text->texture[i].img)
			return (gettextdirerr(text, info, dir, tmp));
		text->texture[i].addr = mlx_get_data_addr(text->texture[i].img, \
			&text->texture[i].bits_per_pixel, &text->texture[i].line_length, \
			&text->texture[i].endian);
		free(tmp);
	}
	return (0);
}

int	gettext(t_texture *text, t_info *info)
{
	DIR	*dir;

	dir = opendir(text->path);
	text->numtext = 0;
	if (!dir)
	{
		if (gettextnodir(text, info))
			return (1);
	}
	else
	{
		if (gettextdir(text, info, dir))
			return (1);
	}
	closedir(dir);
	return (0);
}

int	gettexture(t_info *info)
{
	if (!info->door.path)
		info->door.path = ft_strdup(DOOR_PATH);
	if (!info->exit.path)
		info->exit.path = ft_strdup(EXIT_PATH);
	if (gettext(&info->no, info) || gettext(&info->so, info) \
			|| gettext(&info->we, info) || gettext(&info->ea, info) \
			|| gettext(&info->door, info) || gettext(&info->exit, info))
		return (1);
	return (0);
}

void	handle_doors(t_info *info)
{
	t_door	*current;

	current = info->doors;
	while (current)
	{
		if ((int)info->player.x == current->x \
				&& (int)info->player.y == current->y)
		{
			current->opened_time = 0;
			current->visible = 0;
			current->motion = 0;
		}
		else
		{
			if (current->opened_time == 60)
				current->motion = 1;
			if (current->motion == -1)
				current->visible -= 2;
			else if (current->motion == 1)
				current->visible += 2;
			else if (current->visible == 0 && current->motion == 0)
				current->opened_time += 1;
			if (current->visible < 0)
			{
				current->visible = 0;
				current->motion = 0;
				current->opened_time = 1;
			}
			else if (current->visible > 100)
			{
				current->visible = 100;
				current->motion = 0;
				current->opened_time = 0;
			}
		}
		current = current->next;
	}
}

void	loop1(t_info *info)
{
	handle_doors(info);
	if (info->movement & 1 && !(info->movement & (1 << 1)))
		goforward(info);
	if (info->movement & (1 << 1) && !(info->movement & 1))
		goback(info);
	if (info->movement & (1 << 2) && !(info->movement & (1 << 3)))
		goleft(info);
	if (info->movement & (1 << 3) && !(info->movement & (1 << 2)))
		goright(info);
	if (info->movement & (1 << 4) && !(info->movement & (1 << 5)))
		turnright(info);
	if (info->movement & (1 << 5) && !(info->movement & (1 << 4)))
		turnleft(info);
	info->current_img += 1;
	if (info->current_img >= NB_IMG)
		info->current_img = 0;
	if (info->no.numtext == info->no.numtextmax - 1)
		info->no.numtext = 0;
	else
		info->no.numtext++;
	if (info->so.numtext == info->so.numtextmax - 1)
		info->so.numtext = 0;
	else
		info->so.numtext++;
}

void	loop2(t_info *info)
{
	if (info->we.numtext == info->we.numtextmax - 1)
		info->we.numtext = 0;
	else
		info->we.numtext++;
	if (info->ea.numtext == info->ea.numtextmax - 1)
		info->ea.numtext = 0;
	else
		info->ea.numtext++;
	if (info->door.numtext == info->door.numtextmax - 1)
		info->door.numtext = 0;
	else
		info->door.numtext++;
	if (info->exit.numtext == info->exit.numtextmax - 1)
		info->exit.numtext = 0;
	else
		info->exit.numtext++;
	raisewalls(info);
	if (info->tabmap)
		putmaptoimg(info, &info->img[info->current_img]);
	else
		putminimap(info, &info->img[info->current_img]);
}

int	loop(t_info *info)
{
	loop1(info);
	loop2(info);
	if (info->click && info->xmouse != info->newxmouse)
	{
		info->player.angle -= ((double)(info->xmouse - info->newxmouse) \
				/ (double)WIDTH) * (M_PI / 2);
		info->xmouse = info->newxmouse;
	}
	if (info->map[(int)info->player.y][(int)info->player.x] == 'X')
		closewin(info);
	mlx_do_sync(info->mlx);
	mlx_put_image_to_window(info->mlx, info->win, \
			info->img[info->current_img].img, 0, 0);
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

void	hook_list(t_info *info)
{
	loop(info);
	mlx_do_key_autorepeatoff(info->mlx);
	mlx_hook(info->win, 17, 0, closewin, info);
	mlx_hook(info->win, 2, 1L << 0, hook, info);
	mlx_hook(info->win, 3, 1L << 1, hook_release, info);
	mlx_hook(info->win, 4, 1L << 2, mouse_press, info);
	mlx_hook(info->win, 5, 1L << 3, mouse_release, info);
	mlx_hook(info->win, 6, 1L << 6, mouse_move, info);
	mlx_loop_hook(info->mlx, loop, info);
	mlx_loop(info->mlx);
}

int	mlx(t_info *info)
{
	int	i;

	info->movement = 0;
	info->tabmap = 0;
	info->click = 0;
	info->mlx = mlx_init();
	if (gettexture(info))
		return (1);
	info->win = mlx_new_window(info->mlx, WIDTH, HEIGHT, "cub3D");
	i = 0;
	while (i < NB_IMG)
	{
		info->img[i].img = mlx_new_image(info->mlx, WIDTH, HEIGHT);
		info->img[i].addr = mlx_get_data_addr(info->img[i].img, \
				&info->img[i].bits_per_pixel, &info->img[i].line_length, \
				&info->img[i].endian);
		i++;
	}
	info->current_img = i;
	hook_list(info);
	return (0);
}
