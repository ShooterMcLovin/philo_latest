/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:57:38 by alpicard          #+#    #+#             */
/*   Updated: 2023/04/01 14:18:30 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_info(t_info *info, char **av)
{
	pthread_mutex_init(&info->m_display, NULL);
	pthread_mutex_init(&info->m_pause, NULL);
	pthread_mutex_init(&info->m_eat, NULL);
	pthread_mutex_init(&info->m_sleep, NULL);
	pthread_mutex_init(&info->m_test, NULL);
	info->no_of_philos = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	info->all_alive = 1;
	info->no_of_fulls = 0;
	info->start_time = get_time();
	if (av[5])
		info->no_of_meals = ft_atoi(av[5]);
	info->philo = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	if (!info->philo)
		return (0);
	return (1);
}

int	init_philo(t_info *info)
{
	int x = -1;
	while (++x < info->no_of_philos)
	{
		info->philo[x].no = x + 1;
		info->philo[x].start_eat = get_time();
		info->philo[x].no_of_meals = 0;
		info->philo[x].info = info;
		// info->philo->other_fork = NULL;
		pthread_mutex_init(&(info->philo[x]).own_fork, NULL);
		info->philo[x].other_fork = &info->philo[(x + 1)
			% info->no_of_philos].own_fork;
		pthread_create(&info->philo[x].thread, NULL, &routine,
				&(info->philo[x]));
	}
	x = -1;
	while (++x < info->no_of_philos)
		pthread_join(info->philo[x].thread, NULL);
	return (1);
}