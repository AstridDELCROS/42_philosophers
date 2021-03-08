/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelcros <adelcros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 10:59:27 by astriddel         #+#    #+#             */
/*   Updated: 2021/03/04 16:09:25 by astriddel        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>

typedef struct		s_arguments
{
	int			nb_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			must_eat;
	long		begin;
	bool		dead;
	sem_t		*status;
	sem_t		**protection;
	sem_t		*forks;
}					t_arguments;

typedef struct		s_philo_init
{
	int				id;
	int				meals_eaten;
	long			last_meal;
	t_arguments		*arguments;
}					t_philo_init;

int					ft_atoi(const char *str);
int					ft_check_args(int argc, char **argv);
void				ft_itoa(int n, char *str);
size_t				ft_strlen(const char *str);
char				*ft_strjoin(char *s1, char *s2);
int					ft_wrong_args(int argc, char **argv);
long				ft_gettime(void);
void				ft_destroy_mutex(t_arguments *arguments);
void				ft_clean(t_arguments *arguments,
						t_philo_init **philo_init, pid_t **philo);
int					ft_init_arguments(t_arguments *arguments, char **argv);
int					ft_init_philosophers(t_philo_init **philo_init,
						t_arguments *arguments);
int					ft_init_semaphores(t_arguments *arguments);
int					ft_init_threads(pid_t **philo,
						t_arguments *arguments);
void				ft_dead_lock(t_philo_init *philo);
void				*ft_death_deal(void *philosopher);
void				ft_eating(t_philo_init *philo);
void				ft_dealing_with_forks(t_philo_init *philo);
void				*ft_routine(void *philosophers);
int					ft_wrong_args(int argc, char **argv);
void				ft_print_status(t_philo_init *philo, char *status);
void				ft_launch_simulation(t_philo_init *philo_init,
						pid_t **philo, int nb_philos);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);

#endif
