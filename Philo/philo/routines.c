/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 20:00:27 by lhasmi            #+#    #+#             */
/*   Updated: 2023/07/20 16:46:51 by lhasmi           ###   ########.fr       */
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
