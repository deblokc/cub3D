/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:15:58 by tnaton            #+#    #+#             */
/*   Updated: 2021/11/26 09:26:45 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size(int n)
{
	size_t			size;
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

char	*ft_itoa(int n)
{
	char			*dest;
	unsigned int	nb;
	size_t			i;
	int				pow;

	i = 0;
	dest = (char *)malloc(sizeof(char) * (ft_size(n) + 1));
	if (!dest)
		return (NULL);
	pow = ft_size(n);
	if (n < 0)
	{
		pow--;
		nb = -n;
		dest[i++] = '-';
	}
	else
		nb = n;
	while (pow-- > 0)
	{
		dest[i++] = ((nb / power(10, pow)) + '0');
		nb = (nb % power(10, pow));
	}
	dest[i] = '\0';
	return (dest);
}
