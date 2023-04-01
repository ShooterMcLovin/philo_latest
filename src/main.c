/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:56:20 by alpicard          #+#    #+#             */
/*   Updated: 2023/04/01 14:17:59 by alpicard         ###   ########.fr       */
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

	if (check_input(ac, av))
		if (init_info(&info, av))
			init_philo(&info);
	ft_free(&info);
}
