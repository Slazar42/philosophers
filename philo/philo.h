/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 19:52:35 by slazar            #+#    #+#             */
/*   Updated: 2023/09/07 12:00:11 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct tools
{
	int				is_dead;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_of_meals;
	struct timeval	t_0;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death;
	pthread_mutex_t	meals;
}					t_tools;

typedef struct philo
{
	int				n_of_meals;
	int				id;
	int				l_fork;
	int				r_fork;
	long long		last_meal;
	pthread_t		th;
	t_tools			*tools;
}					t_philo;

void				philo_eating(t_philo *ph);
void				routine(void *arg);
int					check_death(t_philo *philo, int update);
void				start_threads(t_philo *philo);
t_philo				*initialisation(t_tools *tools, char **av);
int					check_args_part2(int ac, char **av);
int					check_args(int ac, char **av);
int					check_number_of_meals(t_philo *philo);
long long			gettime(t_tools *tools);
void				ft_usleep(int time, t_philo *ph);
void				ft_destroy(t_philo *philo);
int					ft_atoi(char *str);
void				death(t_philo *philo, char **av);

#endif
