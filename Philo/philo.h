/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 20:15:50 by lhasmi            #+#    #+#             */
/*   Updated: 2023/07/14 23:29:32 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

// there is no function to check if a philosopher died).
// Also, this code doesn't implement a key part of the Dining Philosophers
// problem: the issue of starvation (a philosopher might never get to eat).
typedef struct s_philosophers
{
	int				id;
	long long		last_time_to_eat;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
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
	long long			start;
	pthread_mutex_t		write;
}				t_data;

void				*routine(void *arg);
void				ft_usleep(long time);
long				is_timenow(void);
void	printing(t_philosophers *philosopher, char *msg);

#endif
