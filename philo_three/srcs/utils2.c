/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelcros <adelcros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 08:59:37 by astriddel         #+#    #+#             */
/*   Updated: 2021/03/04 16:09:18 by astriddel        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int	ft_sizecalc(int n)
{
	int	res;

	res = (n <= 0 ? 1 : 0);
	while (n != 0)
	{
		n = n / 10;
		res++;
	}
	return (res);
}

void		ft_itoa(int n, char *str)
{
	unsigned int	num;
	int				size;

	size = ft_sizecalc(n);
	str[size--] = '\0';
	while (size >= 0)
	{
		str[size] = num % 10 + 48;
		num = num / 10;
		size--;
	}
}

size_t		ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void		*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*p_dst;
	char	*p_src;

	if (!dst && !src)
		return (NULL);
	i = 0;
	p_dst = (char *)dst;
	p_src = (char *)src;
	while (i < n)
	{
		*(p_dst + i) = *(p_src + i);
		i += 1;
	}
	return (dst);
}
