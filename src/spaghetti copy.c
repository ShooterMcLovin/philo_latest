/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaghetti copy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 23:20:19 by alpicard          #+#    #+#             */
/*   Updated: 2023/04/06 00:46:12 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/_types/_timeval.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philo
{
	int no;
	long 			start_eat;
	pthread_t thread;
	pthread_mutex_t lock_r;
	pthread_mutex_t *lock_l;
	struct s_info *info;
}	t_philo;

typedef struct s_info
{
	int no_of;
	int stop;
	long 			start_time;
	pthread_mutex_t eat;
	pthread_mutex_t sleep;
	pthread_mutex_t display;
	pthread_mutex_t die;
	t_philo *philo;
}					t_info;

long get_time(void)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return((time.tv_sec * 1000) + (time.tv_usec / 1000));
}


void display(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->info->display);
	if (philo->info->stop == 0)
		printf("%ld %d %s", get_time() - philo->info->start_time, philo->no, str);
	pthread_mutex_unlock(&philo->info->display);
}

void ft_usleep(int ms, t_info *info)
{
	long int time;
	pthread_mutex_lock(&info->sleep);
	time = get_time();
	pthread_mutex_unlock(&info->sleep);
	while (get_time() - time != ms)
		usleep(10);
}
void *routine (void *input)
{
	t_philo *philo;
	int x;
	philo = (t_philo *)input;
	while (philo->info->stop == 0)
	{
		x = pthread_mutex_lock(&philo->lock_r);
		if (x)
			printf("Mutex Error: %d\n", x);

		display(philo, "has taken a fork\n");

		x = pthread_mutex_lock(philo->lock_l);
		if (x)
			printf("Mutex Error: %d\n", x);

		display(philo, "has taken a fork\n");
		philo->start_eat = get_time();
		display(philo, "is spaghetti\n");
		ft_usleep(200, philo->info);
		display(philo, "is sleeping\n");
		x = pthread_mutex_unlock(philo->lock_l);
		if (x)
			printf("Mutex Error: %d\n", x);
			
		x = pthread_mutex_unlock(&philo->lock_r);
		if (x)
			printf("Mutex Error: %d\n", x);
			
		ft_usleep(100, philo->info);
		display(philo, "thinking\n");
		// if (pthread_mutex_lock(&philo->info->die) != 0)
		// 	printf("Mutex Error:  DERR\n\n");
		// if (pthread_mutex_unlock(&philo->info->die)!= 0)
		// 	printf("Mutex Error:  DERR\n\n");
	}
	return(0);
}

int init_p(t_info *info)
{
	int x = -1;
	while (++x < info->no_of)
	{
		info->philo[x].no = x + 1;
		info->philo[x].info = info;
		info->philo[x].start_eat = info->start_time;
		if (pthread_mutex_init(&info->philo[x].lock_r, NULL))
			return(0);
		info->philo[x].lock_l = &info->philo[(x + 1) % info->no_of].lock_r;
	}
	x = -1;
	while (++x < info->no_of)
		if (pthread_create(&info->philo[x].thread, NULL, &routine, &info->philo[x]) != 0)
			return(0);
	x = -1;
	while (++x < info->no_of)
		if (pthread_join(info->philo[x].thread, NULL) != 0)
			return(0);
	return(1);
}

int init(t_info *info)
{
	/*4philos*/
	info->start_time = get_time();
	info->no_of = 4;///////
	info->stop = 0;
	pthread_mutex_init(&info->eat, NULL);
	pthread_mutex_init(&info->sleep, NULL);
	pthread_mutex_init(&info->die, NULL);
	if (!(info->philo = malloc(sizeof(t_philo*) * info->no_of)))
		return(0);
	return(1);
}

int main()
{
	t_info info;

	if (init(&info))
	{
		if(!init_p(&info))
			printf("philo failed");

	}	
	else
		printf("init failed");
	return(0);
}