/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 22:38:24 by lhasmi            #+#    #+#             */
/*   Updated: 2023/07/20 02:31:26 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	process_death(t_philosophers *philosophers, char *msg)
{
	pthread_mutex_lock(&philosophers->data->dead_mutex);
	philosophers->data->dead = true;
	pthread_mutex_unlock(&philosophers->data->dead_mutex);
	printing(philosophers, msg);
}

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
void	philosopher_routine_2(t_philosophers *philosophers)
{
	while (1)
	{
		eating_cycle(philosophers);
		check_death(philosophers);
		if (is_philosopher_dead(philosophers))
			break ;
		if ((philosophers->data->time_to_eat
				+ philosophers->data->time_to_sleep) < philosophers->data->time_to_die)
		{
			printing(philosophers, "is sleeping");
			ft_usleep(philosophers->data->time_to_sleep);
			check_death(philosophers);
			if (is_philosopher_dead(philosophers))
				break ;
			printing(philosophers, "is thinking");
			if ((philosophers->data->time_to_die
					- (philosophers->data->time_to_eat
						+ philosophers->data->time_to_sleep)) > 0)
			{
				ft_usleep(philosophers->data->time_to_die
					- (philosophers->data->time_to_eat
						+ philosophers->data->time_to_sleep));
				process_death(philosophers, "died");
				break ;
			}
		}
		else
		{
			ft_usleep(philosophers->data->time_to_die
				- philosophers->data->time_to_eat);
			process_death(philosophers, "died");
			break ;
		}
	}
}

void	*routine(void *arg)
{
	t_philosophers	*philosophers;

	philosophers = (t_philosophers *)arg;
	sync_start(philosophers);
	if (philosophers->data->time_to_eat * 2 > philosophers->data->time_to_die)
	{
		if (philosophers->id % 2 != 0)
		{
			check_death(philosophers);
			printing(philosophers, "is thinking");
			ft_usleep(philosophers->data->time_to_eat - 1);
		}
		check_death(philosophers);
		philosopher_routine_2(philosophers);
	}
	else
	{
		if (philosophers->id % 2 != 0)
		{
			check_death(philosophers);
			printing(philosophers, "is thinking");
			ft_usleep(philosophers->data->time_to_eat - 1);
		}
		philosopher_routine(philosophers);
	}
	return (NULL);
}
