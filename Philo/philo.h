/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 20:15:50 by lhasmi            #+#    #+#             */
/*   Updated: 2023/07/13 22:04:49 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>


typedef struct s_philosophers[]
{
	int				id;
	long long		time_to_die;
	long long		last_time_to_eat;
	long long		time_to_sleep;
	int				meals_required;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}					t_philosophers;

typedef struct s_data
{
	t_philosophers		**philos;
	bool  				dead;
	// pthread_mutex_t		print;
	// pthread_mutex_t		death;
	// pthread_mutex_t		*fork;
}				t_data;

void				*routine(void *arg);

#endif
