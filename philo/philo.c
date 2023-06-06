/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 19:51:43 by slazar            #+#    #+#             */
/*   Updated: 2023/06/06 21:21:49 by slazar           ###   ########.fr       */
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
    return NULL;
}

void initial_tools(t_tools *t,int ac,char **av)
{
    t->number_of_philosophers = atoi(av[1]);
    t->time_to_die =atoi(av[2]);
    t->time_to_eat = atoi(av[4]);
    t->time_to_sleep =atoi(av[3]);
    if(ac == 6)
        t->number_of_times_each_philosopher_must_eat = atoi(av[5]);
}

t_philo *ft_allocation(t_tools *t,t_philo *philo)
{
    int i;
    
    philo = malloc(sizeof(t_philo)* t->number_of_philosophers);
    t->forks = malloc(sizeof(pthread_mutex_t)* t->number_of_philosophers);
    i = 0;
    while (i < t->number_of_philosophers)
    {
        philo[i].l_fork = i + 1;
        philo[i].id = i + 1;
        philo[i].r_fork = i;
        if (i == t->number_of_philosophers -1)
            philo[i].l_fork = 0;
        philo[i].t = t;
        i++;
    }
    i = 0;
    while (i < t->number_of_philosophers)
        pthread_mutex_init(&t->forks[i++], NULL);
    return (philo);
}

int main(int ac, char **av)
{
    t_philo *philos = NULL;
    t_tools t;
    initial_tools(&t,ac,av);
    philos = ft_allocation(&t,philos);
    int i = 0;
    while (i < t.number_of_philosophers)
    {
        pthread_create(&philos[i].th, NULL, routine, &philos[i]);
        i++;
    }
    i = 0;
    while (i < t.number_of_philosophers)
    {
        pthread_join(philos[i].th, NULL);
        i++;
    }
    return 0;
}
