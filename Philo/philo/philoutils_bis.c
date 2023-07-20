/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoutils_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 22:36:20 by lhasmi            #+#    #+#             */
/*   Updated: 2023/07/20 03:50:40 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_death(t_philosophers *philosophers)
{
	long long	time_since_last_eat;
	long long	time_since_start;

	time_since_last_eat = is_timenow() - philosophers->last_time_to_eat;
	time_since_start = is_timenow() - philosophers->data->start;
	if (time_since_last_eat > philosophers->data->time_to_die
		|| (time_since_start > philosophers->data->time_to_die
			&& philosophers->nb_eat == 0))
	{
		pthread_mutex_lock(&philosophers->data->dead_mutex);
		philosophers->data->dead = true;
		pthread_mutex_unlock(&philosophers->data->dead_mutex);
		printing(philosophers, "died");
	}
}

void	clean_up(t_philosophers *philosophers, t_data *data,
		pthread_mutex_t *forks, int num_philosophers)
{
	int	i;

	i = 0;
	while (i < num_philosophers)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->dead_mutex);
	pthread_mutex_destroy(&data->eat_mutex);
	pthread_mutex_destroy(&data->init_mutex);
	free(forks);
	free(philosophers);
	free(data);
}
