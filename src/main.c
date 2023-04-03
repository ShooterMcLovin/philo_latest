/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:56:20 by alpicard          #+#    #+#             */
/*   Updated: 2023/04/03 03:10:23 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_free(t_info *info)
{
	int	x;

	pthread_mutex_destroy(&info->m_display);
	pthread_mutex_destroy(&info->m_pause);
	pthread_mutex_destroy(&info->m_sleep);
	pthread_mutex_destroy(&info->m_test);
	x = -1;
	while (++x < info->no_of_philos)
		pthread_mutex_destroy(&info->philo[x].own_fork);
	free(info->philo);
}

int	main(int ac, char **av)
{
	t_info	info;

	if (ac < 5 || ac > 6)
		return (ft_quit());
	if (check_input(av))
	{
		if (init_info(&info, av))
			if (!init_philo(&info))
				write(1, "patate", 6);
		ft_free(&info);
	}
}
