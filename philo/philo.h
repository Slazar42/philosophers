/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 19:52:35 by slazar            #+#    #+#             */
/*   Updated: 2023/06/06 21:10:42 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<stdio.h>

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
    pthread_t th;
    t_tools *t;
} t_philo;

#endif