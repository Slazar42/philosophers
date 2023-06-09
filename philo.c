/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 19:51:43 by slazar            #+#    #+#             */
/*   Updated: 2023/06/09 23:28:57 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void *routine(void *arg)
{
    t_philo *ph;
    ph = (t_philo*)arg;
    while (1)
    {
        printf("%d\n", ph->id);
        sleep(1);        
    }
}
int ft_atoi(char *str)
{
    int s;

    s = 0;
    while (*str)
    {
        if (!(*str >= '0' && *str <= '9'))
            return(-1);
        s = s * 10 + *str - '0';
        str++;
    }
    return (s);
}

t_philo *initialisation(t_tools *tools, t_philo *philo ,int ac,char **av)
{
    int i;

    tools->number_of_philosophers = ft_atoi(av[1]);
    tools->time_to_die = ft_atoi(av[2]);
    tools->time_to_eat = ft_atoi(av[4]);
    tools->time_to_sleep = ft_atoi(av[3]);
    tools->number_of_times_each_philosopher_must_eat = -1;
    if(ac == 6)
        tools->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
    philo = malloc(sizeof(t_philo)* tools->number_of_philosophers);
    tools->forks = malloc(sizeof(pthread_mutex_t)* tools->number_of_philosophers);
    i = -1;
    while (++i < tools->number_of_philosophers)
    {
        philo[i].l_fork = i + 1;
        philo[i].id = i + 1;
        philo[i].r_fork = i;
        if (i == tools->number_of_philosophers -1)
            philo[i].l_fork = 0;
        philo[i].tools = tools;
    }
    i = -1;
    while (++i < tools->number_of_philosophers)
        pthread_mutex_init(&tools->forks[i], NULL);
    return (philo);
}
void check_args_part2(int ac,char **av)
{
    if (ft_atoi(av[4]) < 60)
    {
        printf("Error: wrong time to sleep\n");
        exit(1);
    }
    else if (ac == 6 && ft_atoi(av[5]) < 0)
    {
        printf("Error: wrong number of times each philosopher must eat\n");
        exit(1);
    }
    else if ( ft_atoi(av[1]) < 0 || ft_atoi(av[2]) < 0 || ft_atoi(av[3]) < 0 || ft_atoi(av[4]) < 0)
    {
        printf("Error: wrong argument\n");
        exit(1);
    }
}
void check_args(int ac, char **av)
{
    if (ac < 5 || ac > 6)
    {
        printf("Error: wrong number of arguments\n");
        exit(1);
    }
    else if (ft_atoi(av[1]) < 1)
    {
        printf("Error: wrong number of philosophers\n");
        exit(1);
    }
    else if (ft_atoi(av[2]) < 60)
    {
        printf("Error: wrong time to die\n");
        exit(1);
    }
    else if (ft_atoi(av[3]) < 60)
    {
        printf("Error: wrong time to eat\n");
        exit(1);
    }
    check_args_part2(ac,av);
}
int main(int ac, char **av)
{
    t_philo *philo = NULL;
    t_tools tools;

    check_args(ac,av);
    philo = initialisation(&tools,philo,ac,av);
    int i = -1;
    while (++i < tools.number_of_philosophers)
        pthread_create(&philo[i].th, NULL, routine, &philo[i]);
    i = -1;
    while (++i < tools.number_of_philosophers)
        pthread_join(philo[i].th, NULL);
    return 0;
}
