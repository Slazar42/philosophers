/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 19:51:43 by slazar            #+#    #+#             */
/*   Updated: 2023/08/31 16:44:39 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*initialisation(t_tools *tools, t_philo *philo, char **av)
{
	int	i;

	tools->number_of_philosophers = ft_atoi(av[1]);
	tools->time_to_die = ft_atoi(av[2]);
	tools->time_to_eat = ft_atoi(av[3]);
	tools->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		tools->max_of_meals = ft_atoi(av[5]);
	tools->is_dead = 0;
	philo = malloc(sizeof(t_philo) * tools->number_of_philosophers);
	i = -1;
	while (++i < tools->number_of_philosophers)
	{
		philo[i].l_fork = i + 1;
		philo[i].id = i + 1;
		philo[i].r_fork = i;
		if (i == tools->number_of_philosophers - 1)
			philo[i].l_fork = 0;
		philo[i].tools = tools;
	}
	gettimeofday(&tools->t_0, 0);
	i = -1;
	while (++i < tools->number_of_philosophers)
		pthread_mutex_init(&tools->forks[i], NULL);
	return (philo);
}

int	check_args_part2(int ac, char **av)
{
	if (ft_atoi(av[1]) > 200)
	{
		printf("\x1B[31mError: wrong number of philosophers\n");
		return (0);
	}
	else if (ft_atoi(av[4]) < 60)
	{
		printf("\x1B[31mError: wrong time to sleep\n");
		return (0);
	}
	else if (ac == 6 && ft_atoi(av[5]) < 0)
	{
		printf("\x1B[31mError: wrong max eat number\n");
		return (0);
	}
	else if (ft_atoi(av[1]) < 0 || ft_atoi(av[2]) < 0 || ft_atoi(av[3]) < 0
		|| ft_atoi(av[4]) < 0)
	{
		printf("\x1B[31mError: wrong argument\n");
		return (0);
	}
	return (1);
}

int	check_args(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		printf("\x1B[31mError: wrong number of arguments\n");
		return (0);
	}
	else if (ft_atoi(av[1]) < 1)
	{
		printf("\x1B[31mError: wrong number of philosophers\n");
		return (0);
	}
	else if (ft_atoi(av[2]) < 60)
	{
		printf("\x1B[31mError: wrong time to die\n");
		return (0);
	}
	else if (ft_atoi(av[3]) < 60)
	{
		printf("\x1B[31mError: wrong time to eat\n");
		return (0);
	}
	if (!check_args_part2(ac, av))
		return (0);
	return (1);
}

int	check_number_of_meals(t_philo *philo)
{
	int	id;

	id = 0;
	while (id < philo->tools->number_of_philosophers)
	{
		if (philo[id].n_of_meals <= philo->tools->max_of_meals)
			return (0);
		id++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	int		j;
	t_philo	*philo;
	t_tools	tools;

	j = 0;
	philo = NULL;
	if (!check_args(ac, av))
		return (0);
	philo = initialisation(&tools, philo, av);
	pthread_mutex_init(&tools.print_lock, 0);
	start_threads(philo);
	while (1)
	{
		if (gettime(&tools) - philo[j].last_meal >= philo->tools->time_to_die)
		{
			philo->tools->is_dead = 1;
			pthread_mutex_lock(&tools.print_lock);
			printf("\x1B[31m%lld %d died\n", gettime(philo[j].tools),
				philo[j].id);
			return (0);
		}
		if (av[5] && check_number_of_meals(philo))
			return (0);
		j = (j + 1) % philo->tools->number_of_philosophers;
	}
}
