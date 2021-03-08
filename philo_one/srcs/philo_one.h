/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelcros <adelcros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 10:59:27 by astriddel         #+#    #+#             */
/*   Updated: 2021/03/03 03:30:31 by astriddel        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct		s_args
{
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	long			begin;
	bool			dead;
	pthread_mutex_t	status;
	pthread_mutex_t	*protection;
	pthread_mutex_t	*forks;
}					t_args;

typedef struct		s_philo_init
{
	int				id;
	int				meals_eaten;
	long			last_meal;
	t_args			*args;
}					t_philo_init;

int					ft_atoi(const char *str);
int					ft_check_args(int argc, char **argv);
int					ft_wrong_args(int argc, char **argv);
long				ft_gettime(void);
void				ft_destroy_mutex(t_args *args);
void				ft_clean(t_args *args, t_philo_init **philo_init,
						pthread_t **philo, pthread_t **death_deal);
int					ft_init_arguments(t_args *args, char **argv);
int					ft_init_philosophers(t_philo_init **philo_init,
						t_args *args);
int					ft_init_mutex(t_args *args, pthread_t **philo,
						pthread_t **death_deal);
void				ft_dead_lock(t_philo_init *philo);
void				*ft_death_deal(void *philosopher);
void				ft_eating(t_philo_init *philo);
void				ft_dealing_with_forks(t_philo_init *philo);
void				*ft_routine(void *philosophers);
int					ft_wrong_args(int argc, char **argv);
void				ft_print_status(t_philo_init *philo,
						char *status);
void				ft_launch_simulation(t_philo_init *philo_init,
						pthread_t *philo,
						pthread_t *death_deal, int nb_philos);
int					ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
