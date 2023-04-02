/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:58:34 by alpicard          #+#    #+#             */
/*   Updated: 2023/04/02 16:33:17 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <pthread.h>

long int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	display(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->info->m_display);
	if (philo->info->all_alive == 1)
		printf("%ld %d %s", (get_time() - philo->info->start_time), philo->no,
			str);
	pthread_mutex_unlock(&philo->info->m_display);
}

void	display_stop(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->info->m_display);
	if (philo->info->all_alive == 1 )
	{
		printf("%ld %d %s", (get_time() - philo->info->start_time) - 1 , philo->no,
			str);
			philo->info->all_alive = 0;
	}
	pthread_mutex_unlock(&philo->info->m_display);
}

int min(int time_to_sleep, int time_to_die)
{
	if (time_to_sleep <= time_to_die)
		return(time_to_sleep);
	else
		return(time_to_die);
}

void	ft_usleep(int ms, t_philo *philo)
{
	long int time;
	(void) philo;
	//norm error
	time = get_time();
	while (get_time() != time + ms)
		usleep(10);
}
