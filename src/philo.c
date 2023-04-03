/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:28:23 by alpicard          #+#    #+#             */
/*   Updated: 2023/04/03 03:42:22 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*check_death(void *input)
{
	t_philo	*philo;

	philo = (t_philo *)input;
	ft_usleep(philo->info->time_to_die + 1);
	pthread_mutex_lock(&philo->info->m_eat);
	pthread_mutex_lock(&philo->info->m_pause);
	if (get_time() > philo->start_eat + (long)philo->info->time_to_die)
	{
		pthread_mutex_unlock(&philo->info->m_eat);
		pthread_mutex_unlock(&philo->info->m_pause);
		display(philo, "died -_- \n");
		philo->info->all_alive = 0;
		// philo->info->no_of_fulls = philo->info->no_of_philos;
		
	}
	pthread_mutex_unlock(&philo->info->m_eat);
	pthread_mutex_unlock(&philo->info->m_pause);
	return (0);
}

void	eating(t_philo *philo)
{
	display(philo, "is eating*****\n");
	pthread_mutex_lock(&philo->info->m_eat);
	philo->start_eat = get_time();
	philo->no_of_meals++;
	pthread_mutex_unlock(&(philo->info->m_eat));
	ft_usleep(philo->info->time_to_eat);
	pthread_mutex_unlock(philo->other_fork);
	pthread_mutex_unlock(&(philo->own_fork));
	display(philo, "is sleeping\n");
	ft_usleep(philo->info->time_to_sleep);
	display(philo, "is thinking\n");
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->own_fork);
	display(philo, "has taken a fork\n");
	if (philo->info->no_of_philos == 1)
	{
		ft_usleep(philo->info->time_to_die * 2);
		return ;
	}
	pthread_mutex_lock(philo->other_fork);
	display(philo, "has taken a fork\n");
}

void	*routine(void *input)
{
	t_philo		*philo;
	pthread_t	cd;

	philo = (t_philo *)input;
	if (philo->no % 2 == 0)
	{
		display(philo, "is thinking\n");
		usleep(1);
	}
	while (philo->info->all_alive == 1)
	{
		pthread_create(&cd, NULL, check_death, input);
		take_forks(philo);
		eating(philo);
		pthread_detach(cd);
		if (philo->no_of_meals == philo->info->target_no_of_meals)
		{	
			pthread_mutex_lock(&philo->info->m_pause);
			if (++philo->info->no_of_fulls == philo->info->no_of_philos)
			{
				display(philo, "Done\n");
				philo->info->all_alive = 0;
			}	
			pthread_mutex_unlock(&philo->info->m_pause);
			return (0);
		}
	}
	return (0);
}
