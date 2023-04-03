/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:51:34 by alpicard          #+#    #+#             */
/*   Updated: 2023/04/03 04:10:37 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>


typedef struct s_philo
{
	int				no;
	pthread_t		thread;
	pthread_mutex_t	own_fork;
	pthread_mutex_t	*other_fork;
	long int		start_eat;
	int				no_of_meals;
	struct s_info	*info;
}					t_philo;

typedef struct s_info
{
	int				no_of_philos;
	int				no_of_fulls;
	int				target_no_of_meals;
	long int		start_time;
	int				all_alive;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	t_philo			*philo;
	pthread_mutex_t	m_display;
	pthread_mutex_t	m_pause;
	pthread_mutex_t	m_eat;
	pthread_mutex_t	m_sleep;
	pthread_mutex_t	m_test;
}					t_info;

/*check input*/
int					check_input(char **av);
int					ft_atoi(char *s);
/*utils*/
int					ft_quit(void);
int 				min(int one, int two);
long int			get_time(void);
void				ft_usleep(int ms);
void				display(t_philo *philo, char *str);
void				display_stop(t_philo *philo, char *str);
/*init*/
int					init_info(t_info *info, char **av);
int					init_philo(t_info *info);
/*routine*/
void				*check_death(void *input);
void				*routine(void *input);

#endif