/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 20:39:40 by lhasmi            #+#    #+#             */
/*   Updated: 2023/07/17 20:00:05 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


// bool all_alive(t_philosophers *philosophers, int num_philosophers)
// {
// 	int i = 0;
// 	while (i < num_philosophers)
// 	{
// 		if (is_philosopher_dead(&philosophers[i]))
// 			return false;
// 		i++;
// 	}
// 	return true;
// }

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
	while (is_timenow() < time + start_time)
		usleep(10);
}

void	printing(t_philosophers *philosopher, char *msg)
{
	pthread_mutex_lock(&philosopher->data->write);
	if (is_philosopher_dead(philosopher))
	{
		printf("%lld Philosopher %d %s\n",
			is_timenow() - philosopher->data->start,
			philosopher->id, msg);
		exit(1);
	}
	else
	{
		printf("%lld Philosopher %d %s\n",
			is_timenow() - philosopher->data->start,
			philosopher->id, msg);
	}
	pthread_mutex_unlock(&philosopher->data->write);
}

void	check_death(t_philosophers *philosophers)
{ // Lock 'eat_mutex'
	long long time_since_last_eat = is_timenow() - philosophers->last_time_to_eat;
	printf("philo id %d  time since last eat: %lld\n", philosophers->id, time_since_last_eat);
	long long time_since_start = is_timenow() - philosophers->data->start;
	printf("philo id %d  time since start: %lld\n", philosophers->id, time_since_start);
	// printf("Philosopher  says hi before if\n");

	if (time_since_last_eat > philosophers->data->time_to_die || (time_since_start > philosophers->data->time_to_die && philosophers->nb_eat == 0))
	{
		pthread_mutex_lock(&philosophers->data->dead_mutex);  // Lock 'dead_mutex'
		philosophers->data->dead = true;
		pthread_mutex_unlock(&philosophers->data->dead_mutex);  // Unlock 'dead_mutex'
		// printf("Philosopher  says hi after if\n");
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
