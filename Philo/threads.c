/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 20:00:27 by lhasmi            #+#    #+#             */
/*   Updated: 2023/07/15 22:54:01 by lhasmi           ###   ########.fr       */
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



long long	is_timenow(void)
{
	struct timeval	timenow;

	gettimeofday(&timenow, NULL);
	return (timenow.tv_sec * 1000 + timenow.tv_usec / 1000);
}

// ft_usleep looks good! You can also check for the time of death in there
// and for some edge case protection.
void	ft_usleep(long long time)
{
	long long start_time;

	start_time = is_timenow();
	while (is_timenow() - start_time < time)
		usleep(time);
}

// printing function looks good, but you can imrpove it with a check that makes sure taht mutex is not dead already,
// and for some edge case protection
void	printing(t_philosophers *philosopher, char *msg)
{
	pthread_mutex_lock(&philosopher->data->write);
	if (!philosopher->data->dead)
	{
		printf("%lld Philosopher %d %s\n",
			is_timenow() - philosopher->data->start,
			philosopher->id, msg);
	}
	pthread_mutex_unlock(&philosopher->data->write);
}

// Also you need to sync the philosophers somehow, before the while(1) loop

// You can do so with a mutex lock
void	*routine(void *arg)
{
	t_philosophers	*philosophers;

	philosophers = (t_philosophers *)arg;
	// Wait for the start condition
	// pthread_mutex_lock(&philosophers->data->start_mutex);
	// pthread_cond_wait(&philosophers->data->start_condition, &philosophers->data->start_mutex);
	// pthread_mutex_unlock(&philosophers->data->start_mutex);
	while (1)
	{
		printf("Philosopher %d starting cycle\n", philosophers->id);
		// check flag data.dead
		if (philosophers->data->dead)
			break;
		if ((is_timenow() + philosophers->data->time_to_eat) > philosophers->data->time_to_die)
		{
			philosophers->data->dead = true;
			printing(philosophers, "died");
			break;
		}
		// Philosopher is eating
		pthread_mutex_lock(philosophers->left_fork);
		pthread_mutex_lock(philosophers->right_fork);
		printf("Philosopher %d is eating cycle\n", philosophers->id);
		// print eating (print function calls is_timenow)
		printing(philosophers, "eating");
		philosophers->last_time_to_eat = is_timenow(); // get_time is a function that gets current time
		// call ft_usleep
		ft_usleep(philosophers->data->time_to_eat);
		pthread_mutex_unlock(philosophers->left_fork);
		pthread_mutex_unlock(philosophers->right_fork);

		// Check if philosopher will starve before finishing the next action.
		if ((is_timenow() + philosophers->data->time_to_sleep) > philosophers->data->time_to_die)
		{
			philosophers->data->dead = true;
			printing(philosophers, "died");
			break;
		}
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
		printing(philosophers, "is thinking");
		printf("Philosopher %d finished cycle\n", philosophers->id);
		}
	return NULL;
}

int	main(int argc, char *argv[])
{
	t_data *data;
	data = (t_data *)malloc(sizeof(t_data));
	data->dead = false;
	if (argc < 5)
	{
		printf("Arguments: number_of_philosophers, time_to_die, time_to_eat, time_to_sleep, [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	int num_philosophers = atoi(argv[1]);

	if (num_philosophers <= 0)
	{
		printf("Error: The number of philosophers must be a positive integer.\n");
		return -1;
	}
	pthread_mutex_t	forks[num_philosophers];
	t_philosophers	*philosophers = (t_philosophers *)malloc(sizeof(t_philosophers) * num_philosophers);
	// data->philos = (t_philosophers *)malloc(sizeof(t_philosophers) * num_philosophers);
	// data->philos[i]->id
	// data->philos = philosophers;
	if (philosophers == NULL)
	{
		perror("Failed to allocate memory for philosophers");
		return -1;
	}
	int i = 0;
	// pthread_mutex_init(&data.start_mutex, NULL);
	// pthread_cond_init(&data.start_condition, NULL);
	// pthread_mutex_lock(&data.start_mutex);

	while ( i < num_philosophers)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}

	pthread_mutex_init(&data->write, NULL);

	data->start = is_timenow(); // Set start_time for data.

	data->time_to_die = atoll(argv[2]);
	data->time_to_eat = atoll(argv[3]);
	data->time_to_sleep = atoll(argv[4]);
	data->meals_required = (argc == 6) ? atoll(argv[5]) : -1;
	i = 0;
	while (i < num_philosophers)
	{
		philosophers[i].id = i;
		philosophers[i].left_fork = &forks[i];
		philosophers[i].right_fork = &forks[(i + 1) % num_philosophers];
		philosophers[i].data = data; // Link data to each philosopher.
		if (pthread_create(&philosophers[i].thread, NULL, &routine,
				&philosophers[i]) != 0)
			return (2);
		i++;
	}
	// Now that all threads are created, unlock the start mutex and broadcast the start condition
	// pthread_mutex_unlock(&data.start_mutex);
	// pthread_cond_broadcast(&data.start_condition);

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
	pthread_mutex_destroy(&data->write);
	// pthread_cond_destroy(&data.start_condition);
	// pthread_mutex_destroy(&data.start_mutex);
	free(philosophers);
	return (0);
}
