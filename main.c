/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 23:31:57 by lhasmi            #+#    #+#             */
/*   Updated: 2023/07/22 17:57:54 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_threads(t_philosophers *philosophers, int num_philosophers)
{
	int	i;

	i = 0;
	while (i < num_philosophers)
	{
		if (pthread_join(philosophers[i].thread, NULL) != 0)
			return;
		i++;
	}
}

int	is_input_error(char **s, int arg_count)
{
	int	i;

	i = 0;
	while (i < arg_count)
	{
		if (!ft_isnumber(s[i + 1]) || !ft_isint(s[i + 1]))
		{
			printf("Error: Invalid argument.\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int		check_arguments_and_parse(int argc, char **argv)
{
	int	num_philosophers;
	int	arg_count;

	if (argc < 5 || argc > 6)
	{
		printf("Arguments: number_of_philosophers, time_to_die, time_to_eat,\
				time_to_sleep, [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	arg_count = argc - 1;
	if(is_input_error(argv, arg_count))
		return (1);
	num_philosophers = ft_atoi(argv[1]);
	if (num_philosophers <= 0)
	{
		printf("Error: The number of philosophers must be a positive\
				integer.\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	int				num_philosophers;
	pthread_mutex_t	*forks;
	t_data			*data;
	t_philosophers	*philosophers;

	if(check_arguments_and_parse(argc, argv))
		return (1);
	num_philosophers = ft_atoi(argv[1]);
	philosophers = NULL;
	data = NULL;
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* num_philosophers);
	if (forks == NULL)
	{
		clean_up(philosophers, data, forks, num_philosophers);
		return (1);
	}
	data = init_data(argc, argv);
	philosophers = malloc_philosophers(num_philosophers);
	init_philos_and_forks(philosophers, data, forks, num_philosophers);
	join_threads(philosophers, num_philosophers);
	clean_up(philosophers, data, forks, num_philosophers);
	return (0);
}
