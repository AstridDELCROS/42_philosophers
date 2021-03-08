/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelcros <adelcros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 14:19:52 by astriddel         #+#    #+#             */
/*   Updated: 2021/03/03 03:36:30 by astriddel        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*ft_death_deal(void *philosopher)
{
	t_philo_init *philo;

	philo = philosopher;
	while (philo->args->dead == false)
	{
		pthread_mutex_lock(&philo->args->protection[philo->id]);
		if (ft_gettime() > philo->last_meal + philo->args->time_to_die)
		{
			if (philo->args->must_eat > 0 &&
				philo->meals_eaten >= philo->args->must_eat)
			{
				pthread_mutex_unlock(&philo->args->protection[philo->id]);
				return (NULL);
			}
			ft_print_status(philo, "died");
			pthread_mutex_unlock(&philo->args->protection[philo->id]);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->args->protection[philo->id]);
		usleep(8000);
	}
	return (NULL);
}

void	ft_eating(t_philo_init *philo)
{
	pthread_mutex_lock(&philo->args->protection[philo->id]);
	ft_print_status(philo, "is eating");
	philo->last_meal = ft_gettime();
	philo->meals_eaten = philo->meals_eaten + 1;
	usleep(philo->args->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->args->protection[philo->id]);
}

void	ft_dealing_with_forks(t_philo_init *philo)
{
	pthread_mutex_lock(&philo->args->forks[philo->id]);
	ft_print_status(philo, "has taken a fork");
	if (philo->id == 0)
		pthread_mutex_lock(&philo->args->forks[philo->args->nb_philos - 1]);
	else
		pthread_mutex_lock(&philo->args->forks[philo->id - 1]);
	ft_print_status(philo, "has taken a fork");
	ft_eating(philo);
	pthread_mutex_unlock(&philo->args->forks[philo->id]);
	if (philo->id == 0)
		pthread_mutex_unlock(&philo->args->forks[philo->args->nb_philos - 1]);
	else
		pthread_mutex_unlock(&philo->args->forks[philo->id - 1]);
}

void	*ft_routine(void *philosophers)
{
	t_philo_init *philo;

	philo = (t_philo_init *)philosophers;
	philo->last_meal = ft_gettime();
	while (philo->args->dead == false)
	{
		ft_dealing_with_forks(philo);
		if (philo->args->dead == true || (philo->args->must_eat > 0 &&
					philo->meals_eaten >= philo->args->must_eat))
			return (NULL);
		ft_print_status(philo, "is sleeping");
		usleep(philo->args->time_to_sleep * 1000);
		ft_print_status(philo, "is thinking");
	}
	return (NULL);
}
