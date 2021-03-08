/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelcros <adelcros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 02:15:52 by astriddel         #+#    #+#             */
/*   Updated: 2021/03/03 03:51:15 by astriddel        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	ft_destroy_mutex(t_args *args)
{
	int i;

	i = -1;
	if (args->forks || args->protection)
	{
		while (++i < args->nb_philos)
		{
			pthread_mutex_destroy(&args->forks[i]);
			pthread_mutex_destroy(&args->protection[i]);
		}
		free(args->forks);
		free(args->protection);
	}
	if (args)
		pthread_mutex_destroy(&args->status);
}

void	ft_clean(t_args *args, t_philo_init **philo_init,
		pthread_t **philo, pthread_t **death_deal)
{
	ft_destroy_mutex(args);
	if (*philo_init)
		free(*philo_init);
	if (*philo)
		free(*philo);
	if (*death_deal)
		free(*death_deal);
}
