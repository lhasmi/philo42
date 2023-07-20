/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:28:35 by lhasmi            #+#    #+#             */
/*   Updated: 2023/07/20 16:46:05 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


t_data	*init_data(int argc, char **argv)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	data->dead = false;
	data->num_philosophers = atoi(argv[1]);
	data->time_to_die = atoll(argv[2]);
	data->time_to_eat = atoll(argv[3]);
	data->time_to_sleep = atoll(argv[4]);
	if (argc == 6)
		data->meals_required = atoll(argv[5]);
	else
		data->meals_required = -1;
	data->initialized = false;
	return (data);
}

t_philosophers	*malloc_philosophers(int num_philosophers)
{
	t_philosophers	*philosophers;

	philosophers = (t_philosophers *)malloc(sizeof(t_philosophers)
			* num_philosophers);
	if (philosophers == NULL)
	{
		perror("Failed to allocate memory for philosophers");
		exit(-1);
	}
	return (philosophers);
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
