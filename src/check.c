/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:02:14 by alpicard          #+#    #+#             */
/*   Updated: 2023/04/03 04:07:19 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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

int	ft_quit(void)
{
	write(2, "error: Invalid Input\n", 21);
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
				return (ft_quit());
			i++;
		}
		j++;
	}
	j = 1;
	while (av[j])
		if (ft_atoi(av[j++]) == 0)
			return (ft_quit());
	return (1);
}
