/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 22:38:24 by lhasmi            #+#    #+#             */
/*   Updated: 2023/07/20 22:13:51 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_one(void *arg)
{
	t_philosophers	*philosophers;

	philosophers = (t_philosophers *)arg;
	ft_usleep(philosophers->data->time_to_die);
	pthread_mutex_lock(&philosophers->data->dead_mutex);
	philosophers->data->dead = true;
	pthread_mutex_unlock(&philosophers->data->dead_mutex);
	printing(philosophers, "died");
	return (NULL);
}

void	philosopher_routine(t_philosophers *philosophers)
{
	while (1)
	{
		eating_cycle(philosophers);
		if (is_philosopher_dead(philosophers))
			break ;
		sleeping_cycle(philosophers);
		if (is_philosopher_dead(philosophers))
			break ;
		thinking_cycle(philosophers);
		if (is_philosopher_dead(philosophers))
			break ;
	}
}

void	thinking_for_odds(t_philosophers *philosophers)
{
	if (philosophers->id % 2 != 0)
	{
		check_death(philosophers);
		printing(philosophers, "is thinking");
		ft_usleep(philosophers->data->time_to_eat - 1);
	}
}

void	*routine(void *arg)
{
	t_philosophers	*philosophers;

	philosophers = (t_philosophers *)arg;
	sync_start(philosophers);
	if (philosophers->data->time_to_eat * 2 > philosophers->data->time_to_die)
	{
		thinking_for_odds(philosophers);
		check_death(philosophers);
		philosopher_routine_2(philosophers);
	}
	else
	{
		thinking_for_odds(philosophers);
		philosopher_routine(philosophers);
	}
	return (NULL);
}
