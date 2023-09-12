/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 19:51:43 by slazar            #+#    #+#             */
/*   Updated: 2023/09/07 12:11:12 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*initialisation(t_tools *tools, char **av)
{
	int		i;
	t_philo	*philo;

	tools->number_of_philosophers = ft_atoi(av[1]);
	tools->time_to_die = ft_atoi(av[2]);
	tools->time_to_eat = ft_atoi(av[3]);
	tools->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		tools->max_of_meals = ft_atoi(av[5]);
	philo = malloc(sizeof(t_philo) * tools->number_of_philosophers);
	i = -1;
	gettimeofday(&tools->t_0, 0);
	while (++i < tools->number_of_philosophers)
	{
		philo[i].l_fork = i + 1;
		philo[i].id = i + 1;
		philo[i].r_fork = i;
		if (i == tools->number_of_philosophers - 1)
			philo[i].l_fork = 0;
		philo[i].tools = tools;
		philo[i].n_of_meals = 0;
		philo[i].last_meal = gettime(tools);
		pthread_mutex_init(&tools->forks[i], NULL);
	}
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
	else if (ac == 6 && ft_atoi(av[5]) <= 0)
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
	int	i;
	int	j;

	i = 0;
	while (i < philo->tools->number_of_philosophers)
	{
		pthread_mutex_lock(&philo->tools->meals);
		j = philo->n_of_meals;
		pthread_mutex_unlock(&philo->tools->meals);
		if (j > philo->tools->max_of_meals)
		{
			if (i == philo->tools->number_of_philosophers - 1)
				return (0);
		}
		else
			return (1);
		i++;
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
	tools.forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	philo = initialisation(&tools, av);
	start_threads(philo);
	death(philo, av);
	ft_destroy(philo);
}
