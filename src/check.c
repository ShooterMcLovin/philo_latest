/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:02:14 by alpicard          #+#    #+#             */
/*   Updated: 2023/04/06 08:40:40 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void ftps_fd(int fd, char *s)
{
	if (!s)
	{
		ftps_fd(2, "ftps error\n");
		return;
	}	
	while (*s)
		write(fd, &*s++, 1);
}

int	ft_atoi(char *s)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	while (s[i] != 0)
		res = (res * 10) + (s[i++] - '0');
	if (res < INT_MAX)
		return (res);
	else 
		return(0);
}

int	is_digit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_quit(char *str)
{	
	if (!str)
		write(2, "error: Invalid Input\n", 21);
	else
		ftps_fd(2, str);
	return (0);
}

int	check_input(char **av)
{
	int	i;
	int	j;

	j = 1;
	while (av[j] != NULL)
	{
		i = 0;
		while (av[j][i])
		{
			if (!is_digit(av[j][i]))
				return (ft_quit(NULL));
			i++;
		}
		j++;
	}
	j = 1;
	while (av[j])
	{
		if (ft_atoi(av[j]) == 0 || ft_atoi(av[j]) > 1000)
			return (ft_quit(NULL));
		j++;
	}	
	return (1);
}
