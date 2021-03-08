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

#include "philo_three.h"

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
	{
		printf("number_of_philosopher must be at least : 2\n");
		return (1);
	}
	else if (ft_atoi(argv[2]) < 1 ||
			ft_atoi(argv[3]) < 1 || ft_atoi(argv[4]) < 1)
	{
		printf("times to die, eat or sleep must be at least : 1\n");
		return (1);
	}
	else if (argc == 6 && ft_atoi(argv[5]) < 1)
	{
		printf("number_of_time_each_philosopher_must_eat : 1\n");
		return (1);
	}
	return (0);
}

void	ft_print_status(t_philo_init *philo, char *status)
{
	long timestamp;

	sem_wait(philo->arguments->status);
	timestamp = ft_gettime() - philo->arguments->begin;
	if (philo->arguments->dead == false)
	{
		printf("%ld %3d %s\n", timestamp, philo->id + 1, status);
		if (ft_strncmp(status, "died", 4) == 0)
			philo->arguments->dead = true;
	}
	sem_post(philo->arguments->status);
}

void	ft_launch_simulation(t_philo_init *philo_init,
				pid_t **philo, int nb_philos)
{
	int	i;

	i = -1;
	while (++i < nb_philos)
	{
		(*philo)[i] = fork();
		if ((*philo)[i] == 0)
			ft_routine(&(philo_init[i]));
		else if ((*philo)[i] == -1)
		{
			waitpid(-1, NULL, 0);
			kill(-1, SIGINT);
			printf("perror\n");
			return ;
		}
		usleep(10);
	}
	waitpid(-1, NULL, 0);
	kill(-1, SIGINT);
}

int		main(int argc, char **argv)
{
	t_philo_init	*philo_init;
	t_arguments		arguments;
	pid_t			*philo;

	philo_init = NULL;
	philo = NULL;
	arguments.forks = NULL;
	arguments.protection = NULL;
	arguments.status = NULL;
	if (!(ft_check_args(argc, argv)) ||
			(ft_wrong_args(argc, argv)) ||
			!(ft_init_arguments(&arguments, argv)) ||
			!(ft_init_philosophers(&philo_init, &arguments)) ||
			!(ft_init_threads(&philo, &arguments)) ||
			!(ft_init_semaphores(&arguments)))
	{
		ft_clean(&arguments, &philo_init, &philo);
		return (1);
	}
	ft_launch_simulation(philo_init, &philo, arguments.nb_philos);
	ft_clean(&arguments, &philo_init, &philo);
	return (0);
}
