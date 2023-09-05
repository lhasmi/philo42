/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:28:35 by lhasmi            #+#    #+#             */
/*   Updated: 2023/07/21 23:00:21 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*init_data(int argc, char **argv)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	data->dead = false;
	data->num_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoll(argv[2]);
	data->time_to_eat = ft_atoll(argv[3]);
	data->time_to_sleep = ft_atoll(argv[4]);
	if (argc == 6)
		data->meals_required = ft_atoll(argv[5]);
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
		return (NULL);
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

void	init_philos_and_forks(t_philosophers *philosophers, t_data *data,
		pthread_mutex_t *forks, int num_philosophers)
{
	initialize_mutexes(data, forks, num_philosophers);
	initialize_philosophers(philosophers, data, forks, num_philosophers);
}
