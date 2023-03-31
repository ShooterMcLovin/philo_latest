/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:28:23 by alpicard          #+#    #+#             */
/*   Updated: 2023/03/31 17:15:05 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void thinking(t_philo *philo)
{
	
	display(philo, "is thinking\n");
	ft_usleep(5);


}
void sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->m_sleep);
	display(philo, "is sleeping\n");
	pthread_mutex_unlock(&philo->info->m_sleep);
	ft_usleep(philo->info->time_to_sleep);
}

void eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->m_eat);
	display(philo, "is eating\n");
	philo->start_eat = get_time();
	philo->no_of_meals++;
	pthread_mutex_unlock(&philo->info->m_eat);
	ft_usleep(philo->info->time_to_eat);
	pthread_mutex_unlock(philo->other_fork);
	pthread_mutex_unlock(&philo->own_fork);
}

void take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->own_fork);
	display(philo, "has taken a fork\n");
	pthread_mutex_lock(philo->other_fork);
	display(philo, "has taken a fork\n");
}

void *routine(void *input)
{
	t_philo *philo;
	pthread_t t;
	philo = (t_philo *)input;
	if (philo->no % 2 == 0)
		thinking(philo);
	while (philo->info->all_alive == 1)
	{
		pthread_create(&t, NULL, &check_death, input);
		take_forks(philo);
		eating(philo);
		sleeping(philo);
		pthread_join(t, NULL);
		thinking(philo);
		pthread_detach(t);
	} 

	return(0);
}