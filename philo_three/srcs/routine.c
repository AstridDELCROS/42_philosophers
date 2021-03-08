/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelcros <adelcros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 14:19:52 by astriddel         #+#    #+#             */
/*   Updated: 2021/03/04 16:17:02 by astriddel        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*ft_death_deal(void *philosopher)
{
	t_philo_init *philo;

	philo = philosopher;
	while (philo->arguments->dead == false)
	{
		sem_wait(philo->arguments->protection[philo->id]);
		if (ft_gettime() > philo->last_meal + philo->arguments->time_to_die)
		{
			if (philo->arguments->must_eat > 0 &&
					philo->meals_eaten >= philo->arguments->must_eat)
			{
				sem_post(philo->arguments->protection[philo->id]);
				kill(0, SIGINT);
				return (NULL);
			}
			ft_print_status(philo, "died");
			sem_post(philo->arguments->protection[philo->id]);
			kill(0, SIGINT);
			return (NULL);
		}
		sem_post(philo->arguments->protection[philo->id]);
		usleep(8000);
	}
	return (NULL);
}

void	ft_eating(t_philo_init *philo)
{
	sem_wait(philo->arguments->protection[philo->id]);
	ft_print_status(philo, "is eating");
	philo->last_meal = ft_gettime();
	philo->meals_eaten = philo->meals_eaten + 1;
	usleep(philo->arguments->time_to_eat * 1000);
	sem_post(philo->arguments->protection[philo->id]);
}

void	ft_dealing_with_forks(t_philo_init *philo)
{
	sem_wait(philo->arguments->forks);
	ft_print_status(philo, "has taken a fork");
	sem_wait(philo->arguments->forks);
	ft_print_status(philo, "has taken a fork");
	ft_eating(philo);
	sem_post(philo->arguments->forks);
	sem_post(philo->arguments->forks);
}

void	*ft_routine(void *philosophers)
{
	t_philo_init	*philo;
	pthread_t		death_deal;

	pthread_create(&death_deal, NULL, ft_death_deal, philosophers);
	pthread_detach(death_deal);
	philo = (t_philo_init *)philosophers;
	philo->last_meal = ft_gettime();
	while (philo->arguments->dead == false)
	{
		ft_dealing_with_forks(philo);
		if (philo->arguments->dead == true || (philo->arguments->must_eat > 0 &&
					philo->meals_eaten >= philo->arguments->must_eat))
			return (NULL);
		ft_print_status(philo, "is sleeping");
		usleep(philo->arguments->time_to_sleep * 1000);
		ft_print_status(philo, "is thinking");
	}
	return (NULL);
}
