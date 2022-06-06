/*
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
	while (info->map[y])
		y++;
	while (info->map[0][x])
		x++;
	if (max/(x + 10) > max/(y + 10))
		return (max/(y + 10));
	return (max/(x + 10));
}

void	putplayer(t_img *img, int x, int y, t_info *info, unsigned int color)
{
	int	diff;
	int	nexty;
	int	nextx;
	int	rety;
	int	retx;
	char *dest;

	diff = getdiff(info) + 1;
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
			{
				dest = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
				*(unsigned int*)dest = color; 
			}
			x++;
		}
		y++;
	}
	y = (info->player.y + (-sin(info->player.angle) * STEP)) * diff;
	x = (info->player.x + (cos(info->player.angle) * STEP)) * diff;
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		dest = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
		*(unsigned int*)dest = color; 
	}
	y = (info->player.y + (sin(info->player.angle) * STEP)) * diff;
	x = (info->player.x + (-cos(info->player.angle) * STEP)) * diff;
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		dest = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
		*(unsigned int*)dest = color; 
	}
	y = (info->player.y + (-sin(info->player.angle + (M_PI/2)) * STEP)) * diff;
	x = (info->player.x + (cos(info->player.angle + (M_PI/2)) * STEP)) * diff;
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		dest = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
		*(unsigned int*)dest = color; 
	}
	y = (info->player.y + (-sin(info->player.angle - (M_PI/2)) * STEP)) * diff;
	x = (info->player.x + (cos(info->player.angle - (M_PI/2)) * STEP)) * diff;
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		dest = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
		*(unsigned int*)dest = color; 
	}
}

void	putsquare(t_img *img, int x, int y, t_info *info, unsigned int color)
{
	int	diff;
	int	nexty;
	int	nextx;
	int	retx;
	int	rety;
	char *dest;

	diff = getdiff(info);
	retx = x;
	rety = y;
	nexty = y + diff;
	nextx = x + diff;
	while (y < nexty)
	{
		x = retx;
		while (x < nextx)
		{
			if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
			{
				dest = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
				*(unsigned int*)dest = color; 
			}
			x++;
		}
		y++;
	}
}

void	putmaptoimg(t_info *info, t_img *img)
{
	int	xmap;
	int	ymap;
	int	ximg;
	int	yimg;
	int	diff;

	diff = getdiff(info) + 1;
	ymap = 0;
	ximg = 0;
	yimg = 0;
	while (info->map[ymap])
	{
		xmap = 0;
		ximg = 0;
		while (info->map[ymap][xmap])
		{
			if (info->map[ymap][xmap] == '1')
				putsquare(img, ximg, yimg, info, 0xFFFFFF);
			if (info->map[ymap][xmap] == '0')
				putsquare(img, ximg, yimg, info, 0x0000FF);
			if (info->map[ymap][xmap] == 'N' || info->map[ymap][xmap] == 'W' || info->map[ymap][xmap] == 'E' || info->map[ymap][xmap] == 'S')
				putsquare(img, ximg, yimg, info, 0x00FF00);
			ximg += diff;
			xmap++;
		}
		yimg += diff;
		ymap++;
	}
	putplayer(img, diff * info->player.x, diff * info->player.y, info, 0xFF0000);
}



	int i = 0;
	int j = 0;
	char *dest;
	while (j < HEIGHT / 2)
	{
		i = 0;
		while (i < WIDTH)
		{
			dest = tmp.addr + (j * tmp.line_length + i * (tmp.bits_per_pixel / 8));
			*(unsigned int*)dest = info->c; 
			i++;
		}
		j++;
	}
	while (j < HEIGHT)
	{
		i = 0;
		while (i < WIDTH)
		{
			dest = tmp.addr + (j * tmp.line_length + i * (tmp.bits_per_pixel / 8));
			*(unsigned int*)dest = info->f; 
			i++;
		}
		j++;
	}
	tmp.img = info->no.texture;
	tmp.addr = mlx_get_data_addr(tmp.img, &tmp.bits_per_pixel, &tmp.line_length, &tmp.endian);
	printf("%d\n", tmp.line_length);
	printf("%d\n", tmp.endian);
	printf("%s\n", tmp.addr);
	mlx_put_image_to_window(info->mlx, info->win, info->no.texture, decalage, 0);
	t_img	img;
	img.img = mlx_new_image(info->mlx, (int)ceil((double)info->no.width * factor), (int)ceil((double)info->no.height * factor));
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	int	i;
	int j = 0;
	char	*dst;
	char	*dst2;
	while (j < ((double)info->no.height * factor))
	{
		i = 0;
		while (i < ((double)info->no.width * factor))
		{
			dst = tmp.addr + ((int)round((double)(j * (double)((double)info->no.height / ((double)info->no.height * factor)))) * tmp.line_length + (int)round((double)((double)i * (double)((double)info->no.width / (double)(info->no.width * factor)))) * (tmp.bits_per_pixel / 8));
			dst2 = img.addr + (j * img.line_length + i * (img.bits_per_pixel / 8));
	
			*(unsigned int*)dst2 = *(unsigned int*)dst;
			i++;
		}
		j++;
	}
	decalage += info->no.width;
	mlx_put_image_to_window(info->mlx, info->win, img.img, decalage, 0);
	mlx_put_image_to_window(info->mlx, info->win, info->so.texture, decalage, 0);
	decalage += info->so.width;
	mlx_put_image_to_window(info->mlx, info->win, info->we.texture, decalage, 0);
	decalage += info->we.width;
	mlx_put_image_to_window(info->mlx, info->win, info->ea.texture, decalage, 0);
	decalage += info->ea.width;
*/
