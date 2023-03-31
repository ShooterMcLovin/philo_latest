/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:02:14 by alpicard          #+#    #+#             */
/*   Updated: 2023/03/31 16:22:41 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void *check_death(void *input)
{
	t_philo *philo;
	philo = (t_philo *)input;
	pthread_mutex_lock(&philo->info->m_pause);
	// pthread_mutex_lock(&philo->info->m_eat);
	// pthread_mutex_lock(&philo->info->m_sleep);
	while (1)
	{

	if (get_time() > philo->start_eat + philo->info->time_to_die)
	{
		display(philo, "died");
		philo->info->all_alive = 0;
		// pthread_mutex_unlock(&philo->info->m_eat);
		// pthread_mutex_unlock(&philo->info->m_sleep);
		pthread_mutex_unlock(&philo->info->m_pause);
		return(0);
	}
	}
	// pthread_mutex_unlock(&philo->info->m_eat);
	// pthread_mutex_unlock(&philo->info->m_sleep);
	pthread_mutex_unlock(&philo->info->m_pause);
	return(0);
}
