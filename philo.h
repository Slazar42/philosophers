/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 19:52:35 by slazar            #+#    #+#             */
/*   Updated: 2023/06/09 23:31:11 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/time.h>

typedef struct tools
{   
    int number_of_philosophers; 
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;
    pthread_mutex_t *forks;
} t_tools;

typedef struct philo
{   
    int id;
    int l_fork;
    int r_fork;
    long long last_meal;
    pthread_t th;
    t_tools *tools;
} t_philo;

/*

p_philo {
    int id;
    pthread_mutex_t *l_fork;
    pthread_mutex_t *r_fork;
    long long last_meal;
    pthread_mutex_t *print;
    pthread_mutex_t *sync;
    t_tools *tools;
}

main struct {
    int number_of_philosophers; 
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;
    pthread_mutex_t *forks;
    pthread_mutex_t *print;
    pthread_mutex_t *sync;
    struct p_philo *philo;
    t_philo *philo;
}

forks;
pthread_mutex_lock(sync);
last_meal = gettime();
pthread_mutex_unlock(sync);

while (1)
{
    pthread_mutex_lock(sync);
    if (last_meal + time_to_die < gettime())
        return (0);
    pthread_mutex_unlock(sync);
}

*/

#endif