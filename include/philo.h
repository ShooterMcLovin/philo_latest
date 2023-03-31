/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:51:34 by alpicard          #+#    #+#             */
/*   Updated: 2023/03/31 16:07:32 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdlib.h>
#include <sys/_pthread/_pthread_mutex_t.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

typedef struct s_philo
{
	int no;
	pthread_t thread;
	pthread_mutex_t own_fork;
	pthread_mutex_t *other_fork;
	long int start_eat;
	int no_of_meals;
	int state;
	struct s_info *info;
}	t_philo;

typedef struct s_info
{
	int no_of_philos;
	int no_of_meals;
	long int start_time;
	int all_alive;
	int time_to_eat;
	int time_to_die;
	int time_to_sleep;
	t_philo *philo;
	pthread_mutex_t m_display;
	pthread_mutex_t m_pause;
	pthread_mutex_t m_eat;
	pthread_mutex_t m_sleep;
}	t_info;

/*check input*/
/*utils*/
int ft_atoi(char *s);
long int get_time(void);
void ft_usleep(int ms);
void display(t_philo *philo, char *str);
/*init*/
int init_info(t_info *info, char **av);
int init_philo(t_info *info);
/*routine*/
void *check_death(void *input);
void *routine(void *input);


#endif