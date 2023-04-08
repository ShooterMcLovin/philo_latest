/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:57:38 by alpicard          #+#    #+#             */
/*   Updated: 2023/04/08 10:16:07 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_info(t_info *info, char **av)
{
	int	x;

	x = 0;
	info->no_of_philos = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	info->start_time = get_time();
	info->reqd_meals = -1;
	if (av[5])
		info->reqd_meals = ft_atoi(av[5]);
	info->stop = false;
	x += pthread_mutex_init(&info->pause, NULL);
	x += pthread_mutex_init(&info->display, NULL);
	info->philo = malloc(sizeof(t_philo *) * info->no_of_philos);
	if (x)
		return (0);
	return (1);
}

int	start_routine(t_info *info)
{
	int	x;

	x = -1;
	while (++x < info->no_of_philos)
	{
		info->philo[x].other_fork = &info->philo[(x + 1)
			% info->no_of_philos].own_fork;
	}
	x = -1;
	while (++x < info->no_of_philos)
	{
		if (pthread_create(&info->philo[x].thread, NULL, &routine,
				&info->philo[x]) != 0)
			return (0);
	}
	return (1);
}

int	init_philo(t_info *info)
{
	int			x;
	long long	time;

	x = -1;
	time = get_time();
	while (++x < info->no_of_philos)
	{
		info->philo[x].no = x + 1;
		info->philo[x].no_of_meals = 0;
		info->philo[x].needed_meals = info->reqd_meals;
		info->philo[x].alive = true;
		info->philo[x].full = false;
		info->philo[x].info = info;
		info->philo[x].start_time = info->start_time;
		info->philo[x].death_countdown = info->time_to_die;
		info->philo[x].eat_time = info->time_to_eat;
		info->philo[x].sleep_time = info->time_to_sleep;
		info->philo[x].start_eat = time;
		info->philo[x].other_fork = NULL;
		if (pthread_mutex_init(&info->philo[x].own_fork, NULL) != 0)
			return (0);
	}
	return (start_routine(info));
}

int	end_sim(t_info *info)
{
	int	x;

	x = -1;
	while (++x < info->no_of_philos)
	{
		if (pthread_join(info->philo[x].thread, NULL) != 0)
			return (0);
	}
	return (1);
}
