/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 10:59:11 by alpicard          #+#    #+#             */
/*   Updated: 2023/04/08 10:16:21 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <signal.h>
#include <unistd.h>

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->pause);
	if (get_time() > (philo->start_eat + philo->death_countdown))
	{
		display(philo, "Died (x_x)\n");
		philo->info->stop = true;
		philo->alive = false;
		pthread_mutex_unlock(&philo->info->pause);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->pause);
	return (0);
}

int	take_forks(t_philo *philo)
{
	int	x;

	x = 0;
	check_death(philo);
	x += pthread_mutex_lock(&philo->own_fork);
	display(philo, "has taken a fork\n");
	if (philo->info->no_of_philos == 1)
	{
		ft_usleep(philo->death_countdown * 2, philo);
		return (0);
	}
	x += pthread_mutex_lock(philo->other_fork);
	display(philo, "has taken a fork\n");
	if (x)
		return (0);
	return (1);
}

int	eating(t_philo *philo)
{
	int	x;

	x = 0;
	display(philo, "is eating\n");
	philo->start_eat = get_time();
	philo->no_of_meals++;
	ft_usleep(philo->eat_time, philo);
	x += pthread_mutex_unlock(philo->other_fork);
	x += pthread_mutex_unlock(&philo->own_fork);
	if (philo->no_of_meals == philo->needed_meals)
		philo->full = true;
	check_death(philo);
	if (x)
		return (0);
	return (1);
}

void	*routine(void *in)
{
	t_philo	*philo;

	philo = (t_philo *)in;
	if (philo->no % 2 == 0)
		ft_usleep(philo->eat_time / 10, philo);
	while (philo->full == false && philo->alive == true && !check_death(philo))
	{
		take_forks(philo);
		eating(philo);
		display(philo, "is sleeping\n");
		ft_usleep(philo->sleep_time, philo);
		display(philo, "is thinking\n");
		ft_usleep((philo->eat_time - philo->sleep_time), philo);
	}
	return (0);
}
