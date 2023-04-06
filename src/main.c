/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:56:20 by alpicard          #+#    #+#             */
/*   Updated: 2023/04/06 08:30:22 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_free(t_info *info)
{
	int	x;

	pthread_mutex_destroy(&info->display);
	pthread_mutex_destroy(&info->sleep);
	pthread_mutex_destroy(&info->die);
	x = -1;
	while (++x < info->no_of_philos)
		pthread_mutex_destroy(&info->philo[x].own_fork);
	free(info->philo);
}

int	main(int ac, char **av)
{
	t_info	info;

	if (ac < 5 || ac > 6)
		return (ft_quit(NULL));
	if (check_input(av))
	{
		if (init_info(&info, av))
		{
			if (!init_philo(&info))
				return(ft_quit("error: init failed\n"));
			ft_free(&info);
		}	
	}
}
				
