/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 21:41:42 by lhasmi            #+#    #+#             */
/*   Updated: 2023/07/23 20:44:02 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initialize_philosopher(t_philosophers *philosopher,
		t_philosopher_params params)
{
	philosopher->id = params.id;
	philosopher->left_fork = params.left_fork;
	philosopher->right_fork = params.right_fork;
	philosopher->data = params.data;
	philosopher->last_time_to_eat = params.data->start;
	philosopher->nb_eat = 0;
}

int	create_philosopher_thread(t_philosophers *philosopher,
		int num_philosophers)
{
	if (num_philosophers == 1)
	{
		if (pthread_create(&philosopher->thread, NULL, &routine_one,
				philosopher) != 0)
			return(1);
	}
	else
	{
		if (pthread_create(&philosopher->thread, NULL, &routine,
				philosopher) != 0)
			return(1);
	}
	return (0);
}

int	initialize_philosophers(t_philosophers *philosophers, t_data *data,
		pthread_mutex_t *forks, int num_philosophers)
{
	int						i;
	int						error;
	t_philosopher_params	params;

	i = 0;
	while (i < num_philosophers)
	{
		params.id = i + 1;
		params.data = data;
		params.left_fork = &forks[i];
		params.right_fork = &forks[(i + 1) % num_philosophers];
		initialize_philosopher(&philosophers[i], params);
		error = create_philosopher_thread(&philosophers[i], num_philosophers);
		if (error)
			return (1);
		i++;
	}
	pthread_mutex_lock(&data->init_mutex);
	data->start = is_timenow();
	data->initialized = true;
	pthread_mutex_unlock(&data->init_mutex);
	return (0);
}
