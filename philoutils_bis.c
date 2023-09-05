/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoutils_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 22:36:20 by lhasmi            #+#    #+#             */
/*   Updated: 2023/09/05 19:50:06 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_atoll(const char *str)
{
	size_t		i;
	long long	sign;
	long long	out;

	i = 0;
	sign = 1;
	out = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (is_digit(str[i]))
		out = (out * 10) + (str[i++] - '0');
	return (out * sign);
}

void	process_death(t_philosophers *philosophers, char *msg)
{
	pthread_mutex_lock(&philosophers->data->dead_mutex);
	philosophers->data->dead = true;
	pthread_mutex_unlock(&philosophers->data->dead_mutex);
	if(printing(philosophers, msg))
		return(1);
}

void	check_death(t_philosophers *philosophers)
{
	long long	time_since_last_eat;
	long long	time_since_start;

	time_since_last_eat = is_timenow() - philosophers->last_time_to_eat;
	time_since_start = is_timenow() - philosophers->data->start;
	if (time_since_last_eat > philosophers->data->time_to_die)
		process_death(philosophers, "died");
	else if (time_since_start > philosophers->data->time_to_die
		&& philosophers->nb_eat == 0)
	{
		process_death(philosophers, "died");
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
