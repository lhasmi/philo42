/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 22:07:47 by lhasmi            #+#    #+#             */
/*   Updated: 2023/07/20 23:17:59 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat_sleep_think2(t_philosophers *philosophers)
{
	eating_cycle(philosophers);
	check_death(philosophers);
	if (is_philosopher_dead(philosophers))
		return ;
	printing(philosophers, "is sleeping");
	ft_usleep(philosophers->data->time_to_sleep);
	check_death(philosophers);
	if (is_philosopher_dead(philosophers))
		return ;
	printing(philosophers, "is thinking");
}

void	philo_eat_sleep_die2(t_philosophers *philosophers)
{
	eating_cycle2(philosophers);
	sleeping_cycle(philosophers);
	check_death(philosophers);
	if (is_philosopher_dead(philosophers))
		return ;
	process_death(philosophers, "died");
}

void	philosopher_routine_2(t_philosophers *philosophers)
{
	while (1)
	{
		if ((philosophers->data->time_to_eat
				+ philosophers->data->time_to_sleep)
			< philosophers->data->time_to_die)
		{
			philo_eat_sleep_think2(philosophers);
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
			philo_eat_sleep_die2(philosophers);
			break ;
		}
	}
}
