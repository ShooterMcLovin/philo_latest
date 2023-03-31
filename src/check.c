/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:02:14 by alpicard          #+#    #+#             */
/*   Updated: 2023/03/31 18:48:58 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void *check_death(void *input)
{
	t_philo *philo;

	philo = (t_philo *)input;
	ft_usleep(philo->info->time_to_die + 1);
	pthread_mutex_lock(&philo->info->m_eat);
	pthread_mutex_lock(&philo->info->m_pause);
	if (get_time() > philo->start_eat + philo->info->time_to_die)
	{
		pthread_mutex_unlock(&philo->info->m_eat);
		pthread_mutex_unlock(&philo->info->m_pause);
		display(philo, "died");
		philo->info->all_alive = 0;
		return(0);
	}
	pthread_mutex_unlock(&philo->info->m_eat);
	pthread_mutex_unlock(&philo->info->m_pause);
	return(0);
}
