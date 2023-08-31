/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 16:29:45 by slazar            #+#    #+#             */
/*   Updated: 2023/08/31 16:45:16 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eating(t_philo *ph)
{
	pthread_mutex_lock(&ph->tools->forks[ph->l_fork]);
	pthread_mutex_lock(&ph->tools->forks[ph->r_fork]);
	ph->last_meal = gettime(ph->tools);
	ph->n_of_meals += 1;
	pthread_mutex_lock(&ph->tools->print_lock);
	printf("\x1B[35m%lld %d has taken a fork\n", gettime(ph->tools), ph->id);
	printf("\x1B[32m%lld %d is eating\n", gettime(ph->tools), ph->id);
	pthread_mutex_unlock(&ph->tools->print_lock);
	ft_usleep(ph->tools->time_to_eat, ph);
	pthread_mutex_unlock(&ph->tools->forks[ph->l_fork]);
	pthread_mutex_unlock(&ph->tools->forks[ph->r_fork]);
}

void	philo_sleeping(t_philo *ph)
{
	pthread_mutex_lock(&ph->tools->print_lock);
	printf("\x1B[33m%lld %d is sleeping\n", gettime(ph->tools), ph->id);
	pthread_mutex_unlock(&ph->tools->print_lock);
	ft_usleep(ph->tools->time_to_sleep, ph);
}

void	philo_thinking(t_philo *ph)
{
	pthread_mutex_lock(&ph->tools->print_lock);
	printf("\x1B[34m%lld %d is thinking\n", gettime(ph->tools), ph->id);
	pthread_mutex_unlock(&ph->tools->print_lock);
}

void	routine(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	if (ph->id % 2 == 1)
	{
		printf("\x1B[34m%lld %d is thinking\n", gettime(ph->tools), ph->id);
		ft_usleep(ph->tools->time_to_eat, ph);
	}
	while (!ph->tools->is_dead)
	{
		philo_eating(ph);
		philo_sleeping(ph);
		philo_thinking(ph);
	}
}

void	start_threads(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->tools->number_of_philosophers)
		pthread_create(&philo[i].th, NULL, (void *)routine, &philo[i]);
}
