/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 20:39:40 by lhasmi            #+#    #+#             */
/*   Updated: 2023/07/16 22:02:50 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	sync_start(t_philosophers *philosophers)
{
	while (is_timenow() < philosophers->data->start)
		continue;
}

long long	is_timenow(void)
{
	struct timeval	timenow;

	gettimeofday(&timenow, NULL);
	return (timenow.tv_sec * 1000 + timenow.tv_usec / 1000);
}

void	ft_usleep(long time)
{
	long long start_time;

	start_time = is_timenow();
	while (is_timenow() - start_time < time)
		usleep(time);
}

void	printing(t_philosophers *philosopher, char *msg)
{
	pthread_mutex_lock(&philosopher->data->write);
	if (!philosopher->data->dead)
	{
		printf("%lld Philosopher %d %s\n",
			is_timenow() - philosopher->data->start,
			philosopher->id, msg);
	}
	pthread_mutex_unlock(&philosopher->data->write);
}

void	check_death(t_philosophers *philosophers, char *action)
{
	pthread_mutex_lock(&philosophers->data->eat_mutex);  // Lock 'eat_mutex'
	long long time_since_last_eat = is_timenow() - philosophers->last_time_to_eat;
	pthread_mutex_unlock(&philosophers->data->eat_mutex);  // Unlock 'eat_mutex'

	if ((time_since_last_eat + philosophers->data->time_to_eat) > philosophers->data->time_to_die)
	{
		pthread_mutex_lock(&philosophers->data->dead_mutex);  // Lock 'dead_mutex'
		philosophers->data->dead = true;
		pthread_mutex_unlock(&philosophers->data->dead_mutex);  // Unlock 'dead_mutex'
		printing(philosophers, "died");
	}
	else if ((time_since_last_eat + philosophers->data->time_to_sleep) > philosophers->data->time_to_die && strcmp(action, "sleeping") == 0)
	{
		pthread_mutex_lock(&philosophers->data->dead_mutex);  // Lock 'dead_mutex'
		philosophers->data->dead = true;
		pthread_mutex_unlock(&philosophers->data->dead_mutex);  // Unlock 'dead_mutex'
		printing(philosophers, "died");
	}
}

void	clean_up(t_philosophers *philosophers, t_data *data, pthread_mutex_t *forks, int num_philosophers)
{
	int i = 0;
	while (i < num_philosophers)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->dead_mutex);   // Destroy 'dead_mutex'
	pthread_mutex_destroy(&data->eat_mutex);    // Destroy 'eat_mutex'
	free(philosophers);
	free(data);
}