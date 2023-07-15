/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 20:15:50 by lhasmi            #+#    #+#             */
/*   Updated: 2023/07/15 16:21:40 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>


// TO DO:
// Adressing aspects that could lead to race conditions or deadlocks:

// 1 //  initialize t_data.dead to false and update this flag. Ensure this flag
// is updated properly when a philosopher dies to avoid race conditions.


// 2 //     The usage of mutexes for the forks is correct, but there's a risk of a deadlock
//  situation known as "dining philosophers problem". This can happen if all philosophers
//  pick their left fork simultaneously, then wait for the right fork, which is held by
//  another philosopher. A common solution to this is to enforce an ordering on the
//  acquisition of forks, for example, a philosopher must pick up the lower-numbered
//  fork first.

// 3 //     error checking for the conversion of arguments from strgs to integers/long long
//  integers. If these conversions fail, it could lead to unexpected behavior.


// 4 //     Make sure that pthread_create and pthread_join are successful and
//  handle the error if they're not.

// 5 //     The main thread needs to keep checking if all philosophers have eaten the
// required number of meals (if specified). When this happens, you need to stop all
//  philosophers from eating any further. This requires shared access to the number
//   of meals eaten by each philosopher, which in turn needs to be protected against
//    data races.

// 6 //     The main thread needs to check if any philosopher has died (e.g.,
//  they didn't eat before time_to_die elapsed), and stop the simulation if this happens.
typedef struct s_data t_data;

typedef struct s_philosophers
{
	int				id;
	long long		last_time_to_eat;
	pthread_t		thread;
	// pthread_t       dmonitor_thread;
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
	pthread_mutex_t		start_mutex; // Mutex for the start condition
	pthread_cond_t		start_condition; // Start condition
}				t_data;

void				*routine(void *arg);
void				ft_usleep(long long time);
long long			is_timenow(void);
void				printing(t_philosophers *philosopher, char *msg);

#endif
