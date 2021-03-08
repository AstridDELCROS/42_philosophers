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

#include "philo_three.h"

void	ft_destroy_semaphores(t_arguments *arguments)
{
	int i;

	i = -1;
	if (arguments->forks)
		sem_close(arguments->forks);
	if (arguments->status)
		sem_close(arguments->status);
	i = -1;
	if (arguments->protection)
	{
		while (++i < arguments->nb_philos)
		{
			if (arguments->protection[i])
				sem_close(arguments->protection[i]);
			else
				break ;
		}
		free(arguments->protection);
	}
}

void	ft_clean(t_arguments *arguments,
				t_philo_init **philo_init, pid_t **philo)
{
	ft_destroy_semaphores(arguments);
	if (*philo_init)
		free(*philo_init);
	if (*philo)
		free(*philo);
}
