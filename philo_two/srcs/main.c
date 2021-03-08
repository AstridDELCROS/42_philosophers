/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelcros <adelcros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 06:43:28 by astriddel         #+#    #+#             */
/*   Updated: 2021/03/04 16:24:39 by astriddel        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		ft_check_args(int argc, char **argv)
{
	int i;
	int j;

	if (argc < 5 || argc > 6)
	{
		printf("wrong number of arguments, should be 4 or 5");
		return (0);
	}
	i = 0;
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("arguments must be numbers!");
				return (0);
			}
		}
	}
	return (1);
}

int		ft_wrong_args(int argc, char **argv)
{
	if (ft_atoi(argv[1]) < 2)
		printf("number_of_philosopher must be at least : 2\n");
	else if (ft_atoi(argv[2]) < 1 ||
			ft_atoi(argv[3]) < 1 ||
			ft_atoi(argv[4]) < 1)
		printf("times to die, eat or sleep must be at least : 1\n");
	else if (argc == 6 && ft_atoi(argv[5]) < 1)
		printf("number_of_time_each_philosopher_must_eat : 1\n");
	return (0);
}

void	ft_print_status(t_philo_init *philo, char *status)
{
	long	timestamp;

	sem_wait(philo->args->status);
	timestamp = ft_gettime() - philo->args->begin;
	if (philo->args->dead == false)
	{
		printf("%ld %3d %s\n", timestamp, philo->id + 1, status);
		if (ft_strncmp(status, "died", 4) == 0)
			philo->args->dead = true;
	}
	sem_post(philo->args->status);
}

void	ft_launch_simulation(t_philo_init *philo_init,
		pthread_t *philo, pthread_t *death_deal, int nb_philos)
{
	int i;

	i = 0;
	while (i < nb_philos)
	{
		pthread_create(&(philo[i]), NULL, ft_routine, &(philo_init[i]));
		pthread_create(&(death_deal[i]), NULL, ft_death_deal, &(philo_init[i]));
		i += 2;
	}
	usleep(1000);
	i = 1;
	while (i < nb_philos)
	{
		pthread_create(&(philo[i]), NULL, ft_routine, &(philo_init[i]));
		pthread_create(&(death_deal[i]), NULL, ft_death_deal, &(philo_init[i]));
		i += 2;
	}
	i = -1;
	while (++i < nb_philos)
	{
		pthread_join(philo[i], NULL);
		pthread_join(death_deal[i], NULL);
	}
}

int		main(int argc, char **argv)
{
	t_philo_init	*philo_init;
	t_args			args;
	pthread_t		*philo;
	pthread_t		*death_deal;

	philo_init = NULL;
	philo = NULL;
	death_deal = NULL;
	args.forks = NULL;
	args.protection = NULL;
	args.status = NULL;
	if (!(ft_check_args(argc, argv)) ||
			(ft_wrong_args(argc, argv)) ||
			!(ft_init_arguments(&args, argv)) ||
			!(ft_init_philosophers(&philo_init, &args)) ||
			!(ft_init_threads(&philo, &death_deal, &args)) ||
			!(ft_init_semaphores(&args)))
	{
		ft_clean(&args, &philo_init, &philo, &death_deal);
		return (1);
	}
	ft_launch_simulation(philo_init, philo, death_deal, args.nb_philos);
	ft_clean(&args, &philo_init, &philo, &death_deal);
	return (0);
}
