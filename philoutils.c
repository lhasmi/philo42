/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 20:39:40 by lhasmi            #+#    #+#             */
/*   Updated: 2023/07/22 18:12:22 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_full(t_philosophers *philosophers)
{
	if (philosophers->nb_eat == philosophers->data->meals_required)
		return (true);
	else
		return (false);
}

void	sync_start(t_philosophers *philosophers)
{
	while (philosophers->data->initialized == false)
		usleep(1);
	philosophers->last_time_to_eat = is_timenow();
}

long long	is_timenow(void)
{
	struct timeval	timenow;

	gettimeofday(&timenow, NULL);
	return (timenow.tv_sec * 1000 + timenow.tv_usec / 1000);
}

void	ft_usleep(long time)
{
	long long	start_time;

	start_time = is_timenow();
	while (is_timenow() < time + start_time)
		usleep(200);
}

int	printing(t_philosophers *philosopher, char *msg)
{
	pthread_mutex_lock(&philosopher->data->write);
	if (is_philosopher_dead(philosopher))
	{
		printf("%lld %d %s\n", is_timenow() - philosopher->data->start,
			philosopher->id, msg);
		return (1);
	}
	else
	{
		printf("%lld %d %s\n", is_timenow() - philosopher->data->start,
			philosopher->id, msg);
		return (0);
	}
	pthread_mutex_unlock(&philosopher->data->write);
	return (0);
}
