/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 16:31:13 by tnaton            #+#    #+#             */
/*   Updated: 2022/02/18 19:33:07 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long long	ft_atoi_base(char *nb, char *base)
{
	int					i;
	int					j;
	int					len;
	unsigned long long	num;

	len = ft_strlen(nb);
	i = 0;
	num = 0;
	while (nb[i])
	{
		j = 0;
		while (base[j] && base[j] != nb[i])
			j++;
		num += (j * ft_power(ft_strlen(base), --len));
		i++;
	}
	free(nb);
	return (num);
}
