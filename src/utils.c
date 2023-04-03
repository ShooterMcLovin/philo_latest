/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:58:34 by alpicard          #+#    #+#             */
/*   Updated: 2023/04/03 04:03:23 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	display_stop(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->info->m_display);
	if (philo->info->all_alive == 1)
	{
		printf("%ld %d %s", (get_time() - philo->info->start_time), philo->no,
			str);
		philo->info->all_alive = 0;
	}	
	pthread_mutex_unlock(&philo->info->m_display);
}
void	display(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->info->m_display);
	if (philo->info->all_alive == 1)
		printf("%ld %d %s", (get_time() - philo->info->start_time), philo->no,
			str);
	pthread_mutex_unlock(&philo->info->m_display);
}

int min(int one, int two)
{
	if (one < two)
		return(one);
	else
		return(two);
}


void	ft_usleep(int ms)
{
	long int	time;

	time = get_time();
	while (get_time() - time < ms)
		usleep(5);
}
