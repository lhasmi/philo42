/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 23:31:57 by lhasmi            #+#    #+#             */
/*   Updated: 2023/07/20 04:49:07 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*init_data(int argc, char **argv)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	data->dead = false;
	data->num_philosophers = atoi(argv[1]);
	data->time_to_die = atoll(argv[2]);
	data->time_to_eat = atoll(argv[3]);
	data->time_to_sleep = atoll(argv[4]);
	if (argc == 6)
		data->meals_required = atoll(argv[5]);
	else
		data->meals_required = -1;
	data->initialized = false;
	return (data);
}

t_philosophers	*init_philosophers(int num_philosophers)
{
	t_philosophers	*philosophers;

	philosophers = (t_philosophers *)malloc(sizeof(t_philosophers)
			* num_philosophers);
	if (philosophers == NULL)
	{
		perror("Failed to allocate memory for philosophers");
		exit(-1);
	}
	return (philosophers);
}

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


int	input_error(char *str)
{
	if (!ft_isnumber(str) || !ft_isint(str))
		return (1);
	return (0);
}

int	invalid_arg(int j, char *argv[])
{
	if ( != NULL)
	{
		if (input_error(argv[j]))
			return (1);
	}
	else
	{
		if (input_error(argv[j + 1]))
			return (1);
	}
	return (0);
}



int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (c);
	return (0);
}

void	check_arguments_and_parse(int argc, char *argv[])
{
	int	num_philosophers;
	int	arg_count;
	int	i;

	if (argc < 5 || argc > 6)
	{
		printf("Arguments: number_of_philosophers, time_to_die, time_to_eat, \
                time_to_sleep, [number_of_times_each_philosopher_must_eat]\n");
		exit(1);
	}
	arg_count = ....;
	i = 0;
	while (i < arg_count )
	{
		if (...)
		{
			printf("Error: Invalid argument.\n");
			free_argv(*args);
			exit(1);
		}
		i++;
	}
	num_philosophers = atoi(argv[1]);
	if (num_philosophers <= 0)
	{
		printf("Error: The number of philosophers must be a positive\
				integer.\n");
		exit(-1);
	}
}

int	main(int argc, char *argv[])
{
	int				num_philosophers;
	pthread_mutex_t	*forks;
	t_data			*data;
	t_philosophers	*philosophers;
	char			**args;


	num_philosophers = atoi(args[1]);
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
	data = init_data(argc, args);
	philosophers = init_philosophers(num_philosophers);
	init_philosophers_and_forks(philosophers, data, forks,
		num_philosophers);
	join_threads(philosophers, num_philosophers);
	free_argv(args);
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
