/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 20:15:50 by lhasmi            #+#    #+#             */
/*   Updated: 2023/07/18 22:49:51 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>


typedef struct s_data t_data;

typedef struct s_philosophers
{
	int				id;
	long long		last_time_to_eat;
	int 			nb_eat;
	pthread_t		thread;
	// pthread_t       dmonitor_thread;
	pthread_mutex_t	*left_fork;//mutex fork = hold the fork
	pthread_mutex_t	*right_fork;
	t_data			*data;
} t_philosophers;

typedef struct s_data
{
	t_philosophers		*philos;
	bool				dead;
	long long			time_to_die;
	long long			time_to_eat;
	long long			time_to_sleep;
	int					meals_required;
	int					num_philosophers;
	long long			start;
	bool				initialized;
	pthread_mutex_t		write;
	pthread_mutex_t		dead_mutex;  // New mutex for protecting 'dead' variable
	pthread_mutex_t		eat_mutex;
	pthread_mutex_t		init_mutex;
}				t_data;

void				*routine(void *arg);
void				eating_cycle(t_philosophers *philosophers);
void				sleeping_cycle(t_philosophers *philosophers);
bool				is_philosopher_dead(t_philosophers *philosophers);
void				initialize_philosophers_and_forks(t_philosophers *philosophers, t_data *data, pthread_mutex_t *forks, int num_philosophers);
void	*routine_one(void *arg);
void one_philosopher(t_philosophers *philosophers, t_data *data);

/////////// philooutils.c  /////////
bool				check_full(t_philosophers *philosophers);
void				sync_start(t_philosophers *philosophers);
long long			is_timenow(void);
void				ft_usleep(long time);
void				printing(t_philosophers *philosopher, char *msg);
void				check_death(t_philosophers *philosophers);
void				clean_up(t_philosophers *philosophers, t_data *data, pthread_mutex_t *forks, int num_philosophers);

#endif
