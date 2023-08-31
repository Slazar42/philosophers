/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 16:31:44 by slazar            #+#    #+#             */
/*   Updated: 2023/08/31 16:33:39 by slazar           ###   ########.fr       */
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
		if (s > INT32_MAX)
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
	while (!ph->tools->is_dead)
	{
		usleep(100);
		gettimeofday(&sleep2, 0);
		if (((sleep2.tv_sec * 1000 + sleep2.tv_usec / 1000) - (sleep.tv_sec
					* 1000 + sleep.tv_usec / 1000)) >= time)
			return ;
	}
}

long long	gettime(t_tools *tools)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	return ((time.tv_sec * 1000 + time.tv_usec / 1000) - (tools->t_0.tv_sec
			* 1000 + tools->t_0.tv_usec / 1000));
}
