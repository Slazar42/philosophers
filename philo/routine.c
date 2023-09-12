/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 16:29:45 by slazar            #+#    #+#             */
/*   Updated: 2023/09/07 11:59:41 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(t_philo *ph, char *act, char *color)
{
	if (!check_death(ph, 0))
		printf("%s%lld %d %s\n", color, gettime(ph->tools), ph->id, act);
	return ;
}

void	philo_eating(t_philo *ph)
{
	pthread_mutex_lock(&ph->tools->forks[ph->l_fork]);
	pthread_mutex_lock(&ph->tools->forks[ph->r_fork]);
	ft_print(ph, "has taken a fork", "\x1B[35m");
	ft_print(ph, "has taken a fork", "\x1B[35m");
	ft_print(ph, "is eating", "\x1B[32m");
	pthread_mutex_lock(&ph->tools->meals);
	ph->last_meal = gettime(ph->tools);
	ph->n_of_meals += 1;
	pthread_mutex_unlock(&ph->tools->meals);
	ft_usleep(ph->tools->time_to_eat, ph);
	pthread_mutex_unlock(&ph->tools->forks[ph->l_fork]);
	pthread_mutex_unlock(&ph->tools->forks[ph->r_fork]);
}

void	routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
	{
		ft_print(philo, "is thinking", "\x1B[34m");
		ft_usleep(philo->tools->time_to_eat, philo);
	}
	while (1)
	{
		if (check_death(philo, 0))
			return ;
		philo_eating(philo);
		ft_print(philo, "is sleeping", "\x1B[33m");
		ft_usleep(philo->tools->time_to_sleep, philo);
		ft_print(philo, "is thinking", "\x1B[34m");
	}
}

void	death(t_philo *ph, char **av)
{
	int	i;
	int	j;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&ph->tools->meals);
		j = gettime(ph->tools) - ph[i].last_meal;
		pthread_mutex_unlock(&ph->tools->meals);
		if (ph->tools->time_to_die <= j || (av[5]
				&& check_number_of_meals(ph) == 0))
		{
			check_death(ph, 1);
			if (ph->tools->time_to_die <= j)
				printf("%s%lld %d %s\n", "\x1B[31m", gettime(ph->tools),
					ph[i].id, "died");
			return ;
		}
		i = (i + 1) % ph->tools->number_of_philosophers;
	}
}

void	start_threads(t_philo *philo)
{
	int	i;

	pthread_mutex_init(&philo->tools->print_lock, 0);
	pthread_mutex_init(&philo->tools->death, 0);
	pthread_mutex_init(&philo->tools->meals, 0);
	philo->tools->is_dead = 0;
	i = -1;
	while (++i < philo->tools->number_of_philosophers)
		pthread_mutex_init(&philo->tools->forks[i], 0);
	i = -1;
	while (++i < philo->tools->number_of_philosophers)
		pthread_create(&philo[i].th, NULL, (void *)routine, &philo[i]);
}
