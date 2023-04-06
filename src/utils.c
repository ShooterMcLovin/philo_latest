/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:58:34 by alpicard          #+#    #+#             */
/*   Updated: 2023/04/06 09:28:54 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void ft_usleep(int ms, t_info *info)
{
	long int time;
	pthread_mutex_lock(&info->sleep);
	time = get_time();
	pthread_mutex_unlock(&info->sleep);
	while (get_time() - time != ms)
		usleep(10);
}

void display(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->info->display);
	if (philo->info->stop == 0)
		printf("%ld %d %s", get_time() - philo->info->start_time, philo->no, str);
	pthread_mutex_unlock(&philo->info->display);
}

void display_death(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->info->display);
	if (philo->info->stop == 0)
	{
		philo->info->stop = 1;
		printf("%ld %d %s", get_time() - philo->info->start_time, philo->no, str);
	}	
	pthread_mutex_unlock(&philo->info->display);
}

void display_stop(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->info->display);
	if (philo->info->stop == 0)
	{
		philo->info->stop = 1;
		printf("%s", str);
	}	
	pthread_mutex_unlock(&philo->info->display);
}