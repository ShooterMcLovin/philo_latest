/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:51:34 by alpicard          #+#    #+#             */
/*   Updated: 2023/04/08 10:19:18 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_info
{
	int				no_of_philos;
	int				reqd_meals;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	long long		start_time;
	bool			stop;
	struct t_philo	*philo;
	pthread_mutex_t	pause;
	pthread_mutex_t	display;
}					t_info;

typedef struct t_philo
{
	int				no;
	int				no_of_meals;
	int				needed_meals;
	bool			alive;
	bool			full;
	t_info			*info;
	pthread_t		thread;
	long long		death_countdown;
	long long		start_eat;
	long long		eat_time;
	long long		sleep_time;
	long long		start_time;
	pthread_mutex_t	own_fork;
	pthread_mutex_t	*other_fork;
}					t_philo;

int					check_input(char **av);
int					ft_atoi(char *s);
int					init_info(t_info *info, char **av);
int					init_philo(t_info *info);
int					end_sim(t_info *info);
int					check_death(t_philo *philo);
void				*routine(void *in);
void				display(t_philo *philo, char *str);
long long			get_time(void);
void				ft_usleep(int ms, t_philo *philo);
void				ftps_fd(int fd, char *s);
int					ft_quit(char *str);

#endif