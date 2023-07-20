/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 23:31:57 by lhasmi            #+#    #+#             */
/*   Updated: 2023/07/20 18:58:07 by lhasmi           ###   ########.fr       */
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
			exit(3);
		i++;
	}
}

void	is_input_error(char **s, 	int arg_count)
{
	int i;

	i = 0;
	while (i < arg_count )
	{
		if (!ft_isnumber(s[i + 1]) || !ft_isint(s[i + 1]))
		{
			printf("Error: Invalid argument.\n");
			exit(1);
		}
		i++;
	}
}

void	check_arguments_and_parse(int argc, char **argv)
{
	int	num_philosophers;
	int	arg_count;

	if (argc < 5 || argc > 6)
	{
		printf("Arguments: number_of_philosophers, time_to_die, time_to_eat,\
				time_to_sleep, [number_of_times_each_philosopher_must_eat]\n");
		exit(1);
	}
	arg_count = argc - 1;
	is_input_error(argv, arg_count);
	num_philosophers = ft_atoi(argv[1]);
	if (num_philosophers <= 0)
	{
		printf("Error: The number of philosophers must be a positive\
				integer.\n");
		exit(1);
	}
}

int	main(int argc, char *argv[])
{
	int				num_philosophers;
	pthread_mutex_t	*forks;
	t_data			*data;
	t_philosophers	*philosophers;

	check_arguments_and_parse(argc, argv);
	num_philosophers = ft_atoi(argv[1]);
	philosophers = NULL;
	data = NULL;
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* num_philosophers);
	if (forks == NULL)
	{
		perror("Failed to allocate memory for forks");
		clean_up(philosophers, data, forks, num_philosophers);
		exit(-1);
	}
	data = init_data(argc, argv);
	philosophers = malloc_philosophers(num_philosophers);
	init_philosophers_and_forks(philosophers, data, forks,
		num_philosophers);
	join_threads(philosophers, num_philosophers);
	clean_up(philosophers, data, forks, num_philosophers);
	return (0);
}

// int	main(int argc, char *argv[])
// {
// 	int				num_philosophers;
// 	pthread_mutex_t	forks[num_philosophers];
// 	t_data			*data;
// 	t_philosophers	*philosophers;

// 	check_arguments(argc, argv);
// 	num_philosophers = atoi(argv[1]);
// 	data = init_data(argc, argv);
// 	philosophers = init_philosophers(num_philosophers);
// 	initialize_philosophers_and_forks(philosophers, data, forks,
// 		num_philosophers);
// 	join_threads(philosophers, num_philosophers);
// 	clean_up(philosophers, data, forks, num_philosophers);
// 	return (0);
// }
