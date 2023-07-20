/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 20:00:27 by lhasmi            #+#    #+#             */
/*   Updated: 2023/07/20 03:14:46 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating_cycle(t_philosophers *philosophers)
{
	check_death(philosophers);
	if (check_full(philosophers) == true)
		exit(1);
	pthread_mutex_lock(philosophers->left_fork);
	pthread_mutex_lock(philosophers->right_fork);
	check_death(philosophers);
	printing(philosophers, "has taken a fork");
	printing(philosophers, "has taken a fork");
	printing(philosophers, "is eating");
	philosophers->last_time_to_eat = is_timenow();
	if (!is_philosopher_dead(philosophers))
		philosophers->nb_eat++;
	philosophers->start_last_lunch = is_timenow();
	ft_usleep(philosophers->data->time_to_eat);
	philosophers->end_last_lunch = is_timenow();
	pthread_mutex_unlock(philosophers->left_fork);
	pthread_mutex_unlock(philosophers->right_fork);
}

void	sleeping_cycle(t_philosophers *philosophers)
{
	long long	time_since_last_eat;

	check_death(philosophers);
	time_since_last_eat = is_timenow() - philosophers->last_time_to_eat;
	if ((time_since_last_eat
			+ philosophers->data->time_to_sleep > philosophers->data->time_to_die))
	{
		ft_usleep(philosophers->data->time_to_die
			- (philosophers->data->time_to_eat));
		process_death(philosophers, "died");
	}
	else
	{
		printing(philosophers, "is sleeping");
		ft_usleep(philosophers->data->time_to_sleep);
	}
}

void	thinking_cycle(t_philosophers *philosophers)
{
	check_death(philosophers);
	printing(philosophers, "is thinking");
}

bool	is_philosopher_dead(t_philosophers *philosophers)
{
	bool	is_dead;

	pthread_mutex_lock(&philosophers->data->dead_mutex);
	is_dead = philosophers->data->dead;
	pthread_mutex_unlock(&philosophers->data->dead_mutex);
	return (is_dead);
}

void	initialize_mutexes(t_data *data, pthread_mutex_t *forks,
		int num_philosophers)
{
	int	i;

	i = 0;
	while (i < num_philosophers)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->dead_mutex, NULL);
	pthread_mutex_init(&data->eat_mutex, NULL);
	pthread_mutex_init(&data->init_mutex, NULL);
}

void	initialize_philosophers(t_philosophers *philosophers, t_data *data,
		pthread_mutex_t *forks, int num_philosophers)
{
	int	i;

	i = 0;
	while (i < num_philosophers)
	{
		philosophers[i].id = i + 1;
		philosophers[i].left_fork = &forks[i];
		philosophers[i].right_fork = &forks[(i + 1) % num_philosophers];
		philosophers[i].data = data;
		philosophers[i].last_time_to_eat = data->start;
		philosophers[i].end_last_lunch = data->start;
		philosophers[i].start_last_lunch = data->start;
		philosophers[i].nb_eat = 0;
		if (num_philosophers == 1)
		{
			if (pthread_create(&philosophers[i].thread, NULL, &routine_one,
					&philosophers[i]) != 0)
				exit(2);
		}
		else
		{
			if (pthread_create(&philosophers[i].thread, NULL, &routine,
					&philosophers[i]) != 0)
				exit(2);
		}
		i++;
	}
	pthread_mutex_lock(&data->init_mutex);
	data->start = is_timenow();
	data->initialized = true;
	pthread_mutex_unlock(&data->init_mutex);
}

void	init_philosophers_and_forks(t_philosophers *philosophers,
		t_data *data, pthread_mutex_t *forks, int num_philosophers)
{
	initialize_mutexes(data, forks, num_philosophers);
	initialize_philosophers(philosophers, data, forks, num_philosophers);
}
