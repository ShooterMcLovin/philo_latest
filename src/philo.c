/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:28:23 by alpicard          #+#    #+#             */
/*   Updated: 2023/04/03 16:39:46 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*check_death(void *input)
{
	t_philo	*philo;

	philo = (t_philo *)input;
	ft_usleep(philo->info->time_to_die + 1);
	pthread_mutex_lock(&philo->info->m_pause);
	pthread_mutex_lock(&philo->info->m_eat);
	if (get_time() > philo->start_eat + (long)philo->info->time_to_die)
	{
		display_stop(philo, "died =======-_-========== \n");
		// philo->info->all_alive = 0;
		pthread_mutex_unlock(&philo->info->m_pause);
		pthread_mutex_unlock(&philo->info->m_eat);
		// philo->info->no_of_fulls = philo->info->no_of_philos;
		return (NULL);
		
	}
	pthread_mutex_unlock(&philo->info->m_pause);
	pthread_mutex_unlock(&philo->info->m_eat);
	return (NULL);
}

void	eating(t_philo *philo)
{

	if (++philo->no_of_meals == philo->info->target_no_of_meals && philo->info->target_no_of_meals > 0)
	{
		pthread_mutex_lock(&philo->info->m_pause);
		if (++philo->info->no_of_fulls == philo->info->no_of_philos)
		{
			display_stop(philo, "Done\n");	
			// pthread_mutex_unlock(&philo->info->m_pause);
		}
		pthread_mutex_unlock(&philo->info->m_pause);
	}
	pthread_mutex_unlock(&(philo->info->m_eat));
	ft_usleep(philo->info->time_to_eat);
	pthread_mutex_unlock(&(philo->own_fork));
	pthread_mutex_unlock(philo->other_fork);

	display(philo, "is sleeping\n");
	ft_usleep(philo->info->time_to_sleep);
	display(philo, "is thinking\n");
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&(philo->own_fork));
	display(philo, "has taken a fork\n");
	if (philo->info->no_of_philos == 1)
	{
		ft_usleep(philo->info->time_to_die * 2);
		return ;
	}
	pthread_mutex_lock(philo->other_fork);
	philo->start_eat = get_time();
	display(philo, "has taken a fork\n");
	display(philo, "is eating*****\n");
	pthread_mutex_lock(&(philo->info->m_eat));
}

void	*routine(void *input)
{
	t_philo		*philo;
	pthread_t	cd;

	philo = (t_philo *)input;
	if (philo->no % 2 == 0 )
	{
		ft_usleep(philo->info->time_to_eat);
		display(philo, "is thinking\n");
	}
	while (philo->info->all_alive == 1)
	{
		pthread_create(&cd, NULL, check_death, input);
		take_forks(philo);
		eating(philo);
		pthread_detach(cd);
		
	}
	return (0);
}
