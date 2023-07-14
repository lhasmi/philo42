/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 20:00:27 by lhasmi            #+#    #+#             */
/*   Updated: 2023/07/14 23:37:42 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// They take the left fork, then the right fork, eat, then put the forks down,
// and sleep.
// I need another thread or process to check if a philosopher has waited more than
// "time_to_die" to get a fork and in that case, end the simulation.
// We also assume here that the philosophers don't need to eat a certain number of times,
// they'll
// just keep eating, sleeping, and thinking in a loop forever.
// I need to handel the death of philosophers
// I need to prevent data racing and deadlock
long	is_timenow(void)
{
	struct timeval	timenow;

	gettimeofday(&timenow, NULL);
	return (timenow.tv_sec * 1000 + timenow.tv_usec / 1000);
}

void	ft_usleep(long time)
{
	long start_time;

	start_time = is_timenow();
	while (is_timenow() - start_time < time)
		usleep(time);
}

void	printing(t_philosophers *philosopher, char *msg)
{
	pthread_mutex_lock(&philosopher->data->write);
	if (!philosopher->data->dead)
	{
		printf("%ld Philosopher %d %s\n",
			is_timenow() - philosopher->data->start,
			philosopher->id, msg);
	}
	pthread_mutex_unlock(&philosopher->data->write);
}

void	*routine(void *arg)
{
	t_philosophers	*philosophers;

	philosophers = (t_philosophers *)arg;
	while (1)
	{
		// check flag data.dead
		if (philosophers->data->dead)
			break;

		// Philosopher is eating
		pthread_mutex_lock(philosophers->left_fork);
		pthread_mutex_lock(philosophers->right_fork);
		// print eating (print function calls is_timenow)
		printing(philosophers, "eating");
		philosophers->last_time_to_eat = get_time(); // Assume get_time is a function that gets current time
		// call ft_usleep
		ft_usleep(philosophers->data->time_to_eat);
		pthread_mutex_unlock(philosophers->left_fork);
		pthread_mutex_unlock(philosophers->right_fork);

		// check flag data.dead
		if (philosophers->data->dead)
			break;

		// print sleeping or thinking (print function calls is_timenow)
		printing(philosophers, "is sleeping");
		ft_usleep(philosophers->data->time_to_sleep);

		// check flag data.dead
		if (philosophers->data->dead)
			break;

		// Philosopher is thinking
		printing(philosophers, "is thinking");	}
	return NULL;
}

int	main(int argc, char *argv[])
{
	t_data data;
	int num_philosophers = atoi(argv[1]);
	pthread_mutex_t	forks[num_philosophers];
	t_philosophers	*philosophers = (t_philosophers *)malloc(sizeof(t_philosophers) * num_philosophers);
	if (philosophers == NULL)
	{
		// handle the error
	}
	int i = 0;
	if (argc < 5)
	{
		printf("Arguments: number_of_philosophers, time_to_die, time_to_eat, time_to_sleep, [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}

	while ( i < num_philosophers)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}

	pthread_mutex_init(&data.write, NULL);

	data.start = is_timenow(); // Set start_time for data.

	i = 0;
	while (i < num_philosophers)
	{
		philosophers[i].id = i;
		data.time_to_die = atoll(argv[2]);
		data.time_to_eat = atoll(argv[3]);
		data.time_to_sleep = atoll(argv[4]);
		data.meals_required = (argc == 6) ? atoll(argv[5]) : -1;
		philosophers[i].left_fork = &forks[i];
		philosophers[i].right_fork = &forks[(i + 1) % num_philosophers];
		philosophers[i].data = &data; // Link data to each philosopher.
		if (pthread_create(&philosophers[i].thread, NULL, &routine,
				&philosophers[i]) != 0)
			return (2);
		i++;
	}
	i = 0;
	while (i < num_philosophers)
	{
		if (pthread_join(philosophers[i].thread, NULL) != 0)
			return (3);
		i++;
	}
	i = 0;
	while (i < num_philosophers)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data.write);

	free(philosophers);
	return (0);
}
