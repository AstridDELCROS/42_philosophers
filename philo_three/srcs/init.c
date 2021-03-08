/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelcros <adelcros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 10:07:02 by astriddel         #+#    #+#             */
/*   Updated: 2021/03/04 16:19:12 by astriddel        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	ft_init_arguments(t_arguments *arguments, char **argv)
{
	arguments->nb_philos = ft_atoi(argv[1]);
	arguments->time_to_die = ft_atoi(argv[2]);
	arguments->time_to_eat = ft_atoi(argv[3]);
	arguments->time_to_sleep = ft_atoi(argv[4]);
	if (!(argv[5]))
		arguments->must_eat = 0;
	else
		arguments->must_eat = ft_atoi(argv[5]);
	return (1);
}

int	ft_init_philosophers(t_philo_init **philo_init, t_arguments *arguments)
{
	int	i;

	i = -1;
	arguments->dead = false;
	*philo_init = malloc(sizeof(t_philo_init) * arguments->nb_philos);
	if (!(*philo_init))
		return (0);
	arguments->begin = ft_gettime();
	while (++i < arguments->nb_philos)
	{
		(*philo_init)[i].id = i;
		(*philo_init)[i].meals_eaten = 0;
		(*philo_init)[i].arguments = arguments;
		(*philo_init)[i].last_meal = arguments->begin;
	}
	return (1);
}

int	ft_init_semaphores(t_arguments *arguments)
{
	int		i;
	char	protection_name[17];

	arguments->protection = malloc(sizeof(sem_t) * arguments->nb_philos);
	sem_unlink("/forks");
	sem_unlink("/status");
	if ((arguments->forks = sem_open("/forks", O_CREAT,
			777, arguments->nb_philos)) == SEM_FAILED)
		return (0);
	if ((arguments->status = sem_open("/status", O_CREAT,
			777, 1)) == SEM_FAILED)
		return (0);
	i = -1;
	ft_memcpy(protection_name, "/protection_", 13);
	while (++i < arguments->nb_philos)
	{
		ft_itoa(i, (protection_name + 13));
		sem_unlink(protection_name);
		if ((arguments->protection[i] = sem_open(protection_name,
				O_CREAT, 777, 1)) == SEM_FAILED)
			return (0);
	}
	return (1);
}

int	ft_init_threads(pid_t **philo, t_arguments *arguments)
{
	*philo = malloc(sizeof(pid_t) * arguments->nb_philos);
	if (!(*philo))
		return (0);
	return (1);
}
