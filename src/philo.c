/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:28:23 by alpicard          #+#    #+#             */
/*   Updated: 2023/04/06 08:41:35 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <pthread.h>

void	*check_death(void *input)
{
	t_philo	*philo;

	philo = (t_philo *)input;
	ft_usleep(philo->info->time_to_die + 1, philo->info);
	pthread_mutex_lock(&philo->info->die);
	pthread_mutex_lock(&philo->info->eat);
	if (get_time() > philo->start_eat + philo->info->time_to_die)
	{
		display_stop(philo, "died =======-_-========== \n");
		pthread_mutex_unlock(&philo->info->die);
		pthread_mutex_unlock(&philo->info->eat);
		pthread_mutex_unlock(&philo->own_fork);
		// philo->info->no_of_fulls = philo->info->no_of_philos;
		return (NULL);
		
	}
	pthread_mutex_unlock(&philo->info->die);
	pthread_mutex_unlock(&philo->info->eat);
	return (NULL);
}

void *routine (void *input)
{
	t_philo *philo;
	int x;
	pthread_t check_pulse;
	philo = (t_philo *)input;
	if (philo->no % 2 == 0)
		ft_usleep(philo->info->time_to_eat / 2, philo->info);
	while (philo->info->stop == 0)
	{
		pthread_create(&check_pulse, NULL, check_death, input);
		x = pthread_mutex_lock(&philo->own_fork);
		if (x)
			printf("Mutex Error: %d\n", x);

		display(philo, "has taken a fork\n");

		x = pthread_mutex_lock(philo->other_fork);
		if (x)
			printf("Mutex Error: %d\n", x);

		display(philo, "has taken a fork\n");
		philo->start_eat = get_time();
		display(philo, "is spaghetti-ing\n");
		ft_usleep(philo->info->time_to_eat, philo->info);
		display(philo, "is sleeping\n");
		x = pthread_mutex_unlock(philo->other_fork);
		if (x)
			printf("Mutex Error: %d\n", x);
			
		x = pthread_mutex_unlock(&philo->own_fork);
		if (x)
			printf("Mutex Error: %d\n", x);
			
		ft_usleep(philo->info->time_to_sleep, philo->info);
		display(philo, "thinking\n");
		pthread_detach(check_pulse);
	}
	return(0);
}
