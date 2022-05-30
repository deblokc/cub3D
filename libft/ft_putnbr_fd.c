/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:14:39 by tnaton            #+#    #+#             */
/*   Updated: 2021/11/26 09:31:33 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size(int n)
{
	unsigned int	size;
	unsigned int	nb;

	size = 0;
	if (n < 0)
	{
		size++;
		nb = -n;
	}
	else
		nb = n;
	while (nb > 9)
	{
		nb /= 10;
		size++;
	}
	return (++size);
}

static long	power(int n, int power)
{
	long	rep;

	rep = 1;
	while (power-- > 0)
		rep *= n;
	return (rep);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nb;
	int				pow;
	char			c;

	pow = ft_size(n);
	if (n < 0)
	{
		pow--;
		nb = -n;
		c = '-';
		write(fd, &c, 1);
	}
	else
		nb = n;
	while (pow-- > 0)
	{	
		c = ((nb / power(10, pow)) + '0');
		write(fd, &c, 1);
		nb = (nb % power(10, pow));
	}
}
