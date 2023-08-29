/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 19:52:35 by slazar            #+#    #+#             */
/*   Updated: 2023/06/15 21:55:00 by slazar           ###   ########.fr       */
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
    int is_dead;
    int number_of_philosophers; 
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;
    struct timeval t_0;
    pthread_mutex_t print_lock;
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

long long gettime(t_tools *tools);
void ft_usleep(int time, t_philo *ph);
#endif