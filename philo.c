/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 19:51:43 by slazar            #+#    #+#             */
/*   Updated: 2023/08/31 12:52:07 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void printing(t_philo *ph,char action)
{
    if (ph->tools->is_dead == 1)
        return;
    pthread_mutex_lock(&ph->tools->print_lock);
    if(action == 'f')
        printf("\x1B[35m%lld %d has taken a fork\n", gettime(ph->tools), ph->id);
    else if(action == 'e')
        printf("\x1B[32m%lld %d is eating\n",gettime(ph->tools), ph->id);
    else if(action == 's')
        printf("\x1B[33m%lld %d is sleeping\n",gettime(ph->tools), ph->id);
    else if(action == 't')
        printf("\x1B[34m%lld %d is thinking\n",gettime(ph->tools), ph->id);
    pthread_mutex_unlock(&ph->tools->print_lock);

}
void philo_eating(t_philo *ph)
{
    pthread_mutex_lock(&ph->tools->forks[ph->l_fork]);
    pthread_mutex_lock(&ph->tools->forks[ph->r_fork]);
    printing(ph,'f');
    printing(ph,'f');
    ph->n_of_meals += 1;
    ph->last_meal_time = gettime(ph->tools);
    printing(ph,'e');
    ft_usleep(ph->tools->time_to_eat, ph);
    pthread_mutex_unlock(&ph->tools->forks[ph->l_fork]);
    pthread_mutex_unlock(&ph->tools->forks[ph->r_fork]);
}

void philo_sleeping(t_philo *ph)
{
    printing(ph,'s');
    ft_usleep(ph->tools->time_to_sleep, ph);
}

void philo_thinking(t_philo *ph)
{
    printing(ph,'t');
}

void ft_usleep(int time, t_philo *ph)
{
    struct timeval sleep;
    struct timeval sleep2;

    gettimeofday(&sleep, 0);
    while (!ph->tools->is_dead)
    {
        usleep(100);
        gettimeofday(&sleep2, 0);
        if (((sleep2.tv_sec*1000 + sleep2.tv_usec/1000) - (sleep.tv_sec*1000 + sleep.tv_usec/1000)) >= time)
            return;
    }
}

void routine(void *arg)
{
    t_philo *ph;
        
    ph = (t_philo*)arg;
    if (ph->id %2 == 1)
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

long long gettime(t_tools *tools)
{
    struct timeval time;
    gettimeofday(&time, 0);
    return((time.tv_sec*1000 + time.tv_usec/1000) - (tools->t_0.tv_sec*1000 + tools->t_0.tv_usec/1000));
}

t_philo * initialisation(t_tools *tools, t_philo *philo ,int ac,char **av)
{
    int i;

    tools->number_of_philosophers = ft_atoi(av[1]);
    tools->time_to_die = ft_atoi(av[2]);
    tools->time_to_eat = ft_atoi(av[3]);
    tools->time_to_sleep = ft_atoi(av[4]);
    tools->is_dead = 0;
    if(ac == 6)
        tools->max_of_meals = ft_atoi(av[5]);
    philo = malloc(sizeof(t_philo)* tools->number_of_philosophers);
    tools->forks = malloc(sizeof(pthread_mutex_t)*tools->number_of_philosophers);
    i = -1;
    while (++i < tools->number_of_philosophers)
    {
        philo[i].r_fork = i;
        philo[i].l_fork = i + 1;
        philo[i].id = i + 1;
        if (i == tools->number_of_philosophers -1)
            philo[i].l_fork = 0;
        philo[i].tools = tools;
    }
    gettimeofday(&tools->t_0, 0);
    i = -1;
    while (++i < tools->number_of_philosophers)
        pthread_mutex_init(&tools->forks[i], NULL);
    return (philo);
}

int check_args_part2(int ac,char **av)
{
    if (ft_atoi(av[4]) < 60)
    {
        printf("\x1B[31mError: wrong time to sleep\n");
        return (0);
    }
    else if (ac == 6 && ft_atoi(av[5]) < 0)
    {
        printf("\x1B[31mError: wrong number of times each philosopher must eat\n");
        return (0);
    }
    else if ( ft_atoi(av[1]) < 0 || ft_atoi(av[2]) < 0 || ft_atoi(av[3]) < 0 || ft_atoi(av[4]) < 0)
    {
        printf("\x1B[31mError: wrong argument\n");
        return (0);
    }
    return(1);
}

int check_args(int ac, char **av)
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
    if (!check_args_part2(ac,av))
        return(0);
    return(1);
}

int check_number_of_meals(t_philo *philo)
{
    int id = 0;
    while(id < philo->tools->number_of_philosophers)
    {
        if (philo[id].n_of_meals < philo->tools->max_of_meals)
            return (0);
        id++;
    }
    return(1);
}

int main(int ac, char **av)
{
    int j;
    int i;

    j = 0;
    i = -1;
    t_philo *philo = NULL;
    t_tools tools;
    if (!check_args(ac,av))
        return(0);
    philo = initialisation(&tools,philo,ac,av);
    pthread_mutex_init(&tools.print_lock,NULL);
    while (++i < tools.number_of_philosophers)
        pthread_create(&philo[i].th, NULL,(void *)routine, &philo[i]);
    i = -1;
    while (++i < tools.number_of_philosophers)
        pthread_join(philo[i].th, NULL);
    i = -1;
    while(!philo->tools->is_dead)
    {
        if(gettime(&tools) - philo[j].last_meal_time >= philo->tools->time_to_die)
        {
            pthread_mutex_lock(&tools.print_lock);
            printf("\x1B[31m%lld %d died\n",gettime(philo[j].tools), philo[j].id);
            philo->tools->is_dead = 1;
            while (++i < tools.number_of_philosophers)
                pthread_detach(philo[i].th);
            return(0);
        }
        // if(check_number_of_meals(philo))
        //     break;
        j = (j + 1) % philo->tools->number_of_philosophers;
    }
}