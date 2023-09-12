/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 16:31:44 by slazar            #+#    #+#             */
/*   Updated: 2023/09/07 11:48:21 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	long	s;

	s = 0;
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (-1);
		s = s * 10 + *str - '0';
		if (s > INT_MAX)
			return (-1);
		str++;
	}
	return (s);
}

void	ft_usleep(int time, t_philo *ph)
{
	struct timeval	sleep;
	struct timeval	sleep2;

	gettimeofday(&sleep, 0);
	while (1)
	{
		if (check_death(ph, 0))
			return ;
		usleep(100);
		gettimeofday(&sleep2, 0);
		if (((sleep2.tv_sec * 1000 + sleep2.tv_usec / 1000) - (sleep.tv_sec
					* 1000 + sleep.tv_usec / 1000)) >= time)
			return ;
	}
}

void	ft_destroy(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->tools->number_of_philosophers)
		pthread_join(philo[i].th, NULL);
	i = -1;
	while (++i < philo->tools->number_of_philosophers)
		pthread_mutex_destroy(&philo->tools->forks[i]);
	pthread_mutex_destroy(&philo->tools->meals);
	free(philo->tools->forks);
	free(philo);
}

long long	gettime(t_tools *tools)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	return ((time.tv_sec * 1000 + time.tv_usec / 1000) - (tools->t_0.tv_sec
			* 1000 + tools->t_0.tv_usec / 1000));
}

int	check_death(t_philo *philo, int update)
{
	int	t;

	t = 0;
	pthread_mutex_lock(&philo->tools->death);
	if (update)
		philo->tools->is_dead = 1;
	t = philo->tools->is_dead;
	pthread_mutex_unlock(&philo->tools->death);
	return (t);
}
