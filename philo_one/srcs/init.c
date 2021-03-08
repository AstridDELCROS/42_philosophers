/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelcros <adelcros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 10:07:02 by astriddel         #+#    #+#             */
/*   Updated: 2021/03/03 03:50:42 by astriddel        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	ft_init_arguments(t_args *args, char **argv)
{
	args->nb_philos = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (!(argv[5]))
		args->must_eat = 0;
	else
		args->must_eat = ft_atoi(argv[5]);
	return (1);
}

int	ft_init_philosophers(t_philo_init **philo_init, t_args *args)
{
	int i;

	i = -1;
	args->dead = false;
	*philo_init = malloc(sizeof(t_philo_init) * args->nb_philos);
	if (!(*philo_init))
		return (0);
	args->begin = ft_gettime();
	while (++i < args->nb_philos)
	{
		(*philo_init)[i].id = i;
		(*philo_init)[i].meals_eaten = 0;
		(*philo_init)[i].args = args;
		(*philo_init)[i].last_meal = args->begin;
	}
	return (1);
}

int	ft_init_mutex(t_args *args, pthread_t **philo, pthread_t **death_deal)
{
	int i;

	*philo = malloc(sizeof(t_philo_init) * args->nb_philos);
	*death_deal = malloc(sizeof(t_philo_init) * args->nb_philos);
	if (!(*philo) || !(*death_deal))
		return (0);
	args->forks = malloc(sizeof(pthread_mutex_t) * args->nb_philos);
	args->protection = malloc(sizeof(pthread_mutex_t) * args->nb_philos);
	if (!(args->forks) || !(args->protection))
		return (0);
	i = -1;
	while (++i < args->nb_philos)
	{
		if (pthread_mutex_init(&args->forks[i], NULL) != 0 ||
			pthread_mutex_init(&args->protection[i], NULL) != 0)
			return (0);
	}
	if (pthread_mutex_init(&args->status, NULL) != 0)
		return (0);
	return (1);
}
