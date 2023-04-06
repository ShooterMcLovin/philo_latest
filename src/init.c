/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:57:38 by alpicard          #+#    #+#             */
/*   Updated: 2023/04/06 09:41:46 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_info(t_info *info, char **av)
{
	if (ft_atoi(av[1]) > 200)
		return (0);
	info->no_of_philos = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	info->philo = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	if (!info->philo)
		return (0);
	pthread_mutex_init(&info->eat, NULL);
	pthread_mutex_init(&info->sleep, NULL);
	pthread_mutex_init(&info->die, NULL);
	pthread_mutex_init(&info->display,NULL);
	info->stop = 0;
	info->no_of_fulls = 0;
	info->reqd_no_of_meals = -1;
	info->start_time = get_time();
	if (av[5])
		info->reqd_no_of_meals = ft_atoi(av[5]);
	return (1);
}

int	init_philo(t_info *info)
{
	int x = -1;
	while (++x < info->no_of_philos)
	{
		info->philo[x].no = x + 1;
		info->philo[x].no_meals_eaten = 0;
		info->philo[x].info = info;
		info->philo[x].start_eat = info->start_time;
		pthread_mutex_init(&info->philo[x].own_fork, NULL);
		info->philo[x].other_fork = &info->philo[(x + 1) % info->no_of_philos].own_fork;
		info->start_time = get_time();
	}
	info->start_time = get_time();
	x = -1;
	while (++x < info->no_of_philos)
		if (pthread_create(&info->philo[x].thread, NULL, &routine, &info->philo[x]) != 0)
			return(0);
	x = -1;
	while (++x < info->no_of_philos)
		if (pthread_join(info->philo[x].thread, NULL) != 0)
			return(0);
	return(1);

}


// int init(t_info *info)
// {
// 	/*4philos*/
// 	info->start_time = get_time();
// 	info->no_of = 4;///////


// 	if (!(info->philo = malloc(sizeof(t_philo*) * info->no_of)))
// 		return(0);
// 	return(1);
// }