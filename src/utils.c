/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:58:34 by alpicard          #+#    #+#             */
/*   Updated: 2023/04/08 10:11:33 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(int ms, t_philo *philo)
{
	long	time;

	if (ms < 0)
		return ;
	(void)philo;
	time = get_time();
	while (get_time() < (time + ms) && !check_death(philo))
		usleep(10);
}

void	display(t_philo *philo, char *str)
{
	long long	time;

	pthread_mutex_lock(&philo->info->display);
	time = get_time() - philo->start_time;
	if (philo->alive == true && philo->full == false
		&& philo->info->stop == false)
		printf("%lld %d %s", time, philo->no, str);
	pthread_mutex_unlock(&philo->info->display);
}
