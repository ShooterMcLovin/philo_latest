/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:56:20 by alpicard          #+#    #+#             */
/*   Updated: 2023/04/08 10:16:12 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_quit(char *str)
{
	if (!str)
		write(2, "error: Invalid Input\n", 21);
	else
		ftps_fd(2, str);
	return (0);
}

void	ft_free(t_info *info)
{
	int	x;

	pthread_mutex_destroy(&info->pause);
	pthread_mutex_destroy(&info->display);
	x = -1;
	while (++x < info->no_of_philos)
		pthread_mutex_destroy(&info->philo[x].own_fork);
	free(info->philo);
	free(info);
}

int	main(int ac, char **av)
{
	t_info	*info;

	if (ac < 5 || ac > 6)
		return (ft_quit(NULL));
	info = malloc(sizeof(t_info));
	if (!info)
		return (0);
	if (check_input(av))
	{
		if (!init_info(info, av))
			return (ft_quit("Error: Initialisation Failed\n"));
		if (!init_philo(info))
			return (ft_quit("Error: Initialisation Failed\n"));
		if (!end_sim(info))
			return (ft_quit("Error: Simulation Failed\n"));
		ft_free(info);
	}
	return (0);
}
