/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelcros <adelcros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 08:59:37 by astriddel         #+#    #+#             */
/*   Updated: 2021/03/04 16:09:18 by astriddel        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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

size_t		ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
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

char		*ft_strjoin(char *s1, char *s2)
{
	char	*both_str;
	int		i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	both_str = malloc(sizeof(both_str) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!(both_str))
		return (NULL);
	while (s1[i] != '\0')
	{
		both_str[i] = s1[i];
		i++;
	}
	while (s2[i - ft_strlen(s1)] != '\0')
	{
		both_str[i] = s2[i - ft_strlen(s1)];
		i++;
	}
	both_str[i] = '\0';
	return (both_str);
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
