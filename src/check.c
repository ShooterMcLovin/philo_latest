/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:02:14 by alpicard          #+#    #+#             */
/*   Updated: 2023/04/01 14:14:13 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void *check_death(void *input)
{
	t_philo *philo;

	philo = (t_philo *)input;
	ft_usleep(philo->info->time_to_die + 1);
	pthread_mutex_lock(&philo->info->m_eat);
	pthread_mutex_lock(&philo->info->m_pause);
	if (get_time() > philo->start_eat + philo->info->time_to_die)
	{
		pthread_mutex_unlock(&philo->info->m_eat);
		pthread_mutex_unlock(&philo->info->m_pause);
		display(philo, "died");
		philo->info->all_alive = 0;
		return(0);
	}
	pthread_mutex_unlock(&philo->info->m_eat);
	pthread_mutex_unlock(&philo->info->m_pause);
	return(0);
}

int ft_atoi(char *s)
{
	int i = 0;
	int res = 0;
	while (s[i] != 0)
		res = (res * 10) + (s[i++] - '0');
	return(res);
}

int is_digit(int c)
{
	return(c>= '0' && c <= '9');
}

int ft_quit()
{
	write(2, "error: Invalid Input\n", 21);
	return(0);
}

int check_input(int ac, char **av)
{
	int i;
	int j;
	if (ac < 5 || ac > 6)
		return(ft_quit());	
	j = 1;
	while (av[j] != NULL)
	{
		i = 0;
		while (av[j][i])
		{
			if (!is_digit(av[j][i]))
				return(ft_quit());
			i++;
		}
		j++;
	}
	j = 1;
	while (av[j])
		if (ft_atoi(av[j++]) == 0)
			return(ft_quit());
	return(1);
}	