/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelcros <adelcros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 02:15:52 by astriddel         #+#    #+#             */
/*   Updated: 2021/03/04 15:50:57 by astriddel        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	ft_destroy_semaphores(t_args *args)
{
	int i;

	i = -1;
	if (args->forks)
		sem_close(args->forks);
	if (args->status)
		sem_close(args->status);
	i = -1;
	if (args->protection)
	{
		while (++i < args->nb_philos)
		{
			if (args->protection[i])
				sem_close(args->protection[i]);
			else
				break ;
		}
		free(args->protection);
	}
}

void	ft_clean(t_args *args, t_philo_init **philo_init,
				pthread_t **philo, pthread_t **death_deal)
{
	ft_destroy_semaphores(args);
	if (*philo_init)
		free(*philo_init);
	if (*philo)
		free(*philo);
	if (*death_deal)
		free(*death_deal);
}
