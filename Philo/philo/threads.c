/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 20:00:27 by lhasmi            #+#    #+#             */
/*   Updated: 2023/07/18 20:37:41 by lhasmi           ###   ########.fr       */
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
	printing(philosophers, "is eating");

	// pthread_mutex_lock(&philosophers->data->eat_mutex);  // Lock 'eat_mutex'
	philosophers->last_time_to_eat = is_timenow();
	// pthread_mutex_unlock(&philosophers->data->eat_mutex);  // Unlock 'eat_mutex'
	if(!is_philosopher_dead(philosophers))
		philosophers->nb_eat++;
	ft_usleep(philosophers->data->time_to_eat);
	// printf( "philosophers->id %d, philosophers->nb_eat %d\n", philosophers->id, philosophers->nb_eat);
	pthread_mutex_unlock(philosophers->left_fork);
	pthread_mutex_unlock(philosophers->right_fork);
}


void	sleeping_cycle(t_philosophers *philosophers)
{
	check_death(philosophers);
	long long time_since_last_eat = is_timenow() - philosophers->last_time_to_eat;
	if(time_since_last_eat + philosophers->data->time_to_sleep > philosophers->data->time_to_die)
	{
		// printf("philosophers->data->time_to_die: %lld\n", philosophers->data->time_to_die);
		// printf("time_since_last_eat %lld\n", time_since_last_eat);
		// printf("philosophers->data->time_to_sleep %lld\n", philosophers->data->time_to_sleep);
		// printf("philosophers->data->time_to_eat: %lld\n", philosophers->data->time_to_eat);
		ft_usleep(philosophers->data->time_to_die - (philosophers->data->time_to_eat));
		pthread_mutex_lock(&philosophers->data->dead_mutex);  // Lock 'dead_mutex'
		philosophers->data->dead = true;
		pthread_mutex_unlock(&philosophers->data->dead_mutex);  // Unlock 'dead_mutex'
		// printf("Philosopher  says hi inside the lorenzocase if\n");
		printing(philosophers, "died");
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
	bool is_dead;

	pthread_mutex_lock(&philosophers->data->dead_mutex);  // Lock 'dead_mutex'
	is_dead = philosophers->data->dead;
	pthread_mutex_unlock(&philosophers->data->dead_mutex);  // Unlock 'dead_mutex'
	return is_dead;
}

void	*routine(void *arg)
{
	t_philosophers	*philosophers = (t_philosophers *)arg;
	sync_start(philosophers);
	if (philosophers->id % 2 != 0) // if philosopher's id is odd, let them sleep first.
	{
		// check_death(philosophers);
		// printing(philosophers, "is thinking");
		ft_usleep(philosophers->data->time_to_eat - 1);
	}
	while (1)
	{
		eating_cycle(philosophers);
		if (is_philosopher_dead(philosophers))
			break;
		sleeping_cycle(philosophers);
		if (is_philosopher_dead(philosophers))
			break;
		thinking_cycle(philosophers);
		if (is_philosopher_dead(philosophers))
			break;
	}
	return NULL;
}

void	initialize_philosophers_and_forks(t_philosophers *philosophers, t_data *data, pthread_mutex_t *forks, int num_philosophers)
{
	int i = 0;

	while (i < num_philosophers)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->dead_mutex, NULL);
	pthread_mutex_init(&data->eat_mutex, NULL);
	pthread_mutex_init(&data->init_mutex, NULL);
	i = 0;
	while (i < num_philosophers)
	{
		philosophers[i].id = i + 1;
		philosophers[i].left_fork = &forks[i];
		philosophers[i].right_fork = &forks[(i + 1) % num_philosophers];
		philosophers[i].data = data;
		philosophers[i].last_time_to_eat = data->start;
		philosophers[i].nb_eat = 0;
		if (pthread_create(&philosophers[i].thread, NULL, &routine,
				&philosophers[i]) != 0)
			exit(2);
		i++;
	}
	printf("All philosophers have been created.\n");
	pthread_mutex_lock(&data->init_mutex);
	data->start = is_timenow();
	data->initialized = true;
	pthread_mutex_unlock(&data->init_mutex);
}

void one_philosopher(t_philosophers *philosophers, t_data *data, pthread_mutex_t *forks)
{
	pthread_mutex_init(&forks[0], NULL);
	pthread_mutex_init(&data->dead_mutex, NULL);
	pthread_mutex_init(&data->init_mutex, NULL);
	philosophers[0].id = 1;
	philosophers[0].left_fork = &forks[0];
	philosophers[0].right_fork = &forks[0];
	philosophers[0].data = data;
	philosophers[0].last_time_to_eat = data->start;
	philosophers[0].nb_eat = 0;
	if (pthread_create(&philosophers[0].thread, NULL, &routine,
			&philosophers[0]) != 0)
		exit(2);
	pthread_mutex_lock(&data->init_mutex);
	data->start = is_timenow();
	data->initialized = true;
	pthread_mutex_unlock(&data->init_mutex);
	pthread_mutex_lock(&philosophers->data->dead_mutex);  // Lock 'dead_mutex'
	philosophers->data->dead = true;
	pthread_mutex_unlock(&philosophers->data->dead_mutex);  // Unlock 'dead_mutex'
	printing(philosophers, "died");

}


int	main(int argc, char *argv[])
{
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
	t_data *data = (t_data *)malloc(sizeof(t_data));
	data->dead = false;
	data->num_philosophers = num_philosophers;
	data->time_to_die = atoll(argv[2]);
	data->time_to_eat = atoll(argv[3]);
	data->time_to_sleep = atoll(argv[4]);
	data->meals_required = (argc == 6) ? atoll(argv[5]) : -1;
	data->initialized = false;
	t_philosophers	*philosophers = (t_philosophers *)malloc(sizeof(t_philosophers) * num_philosophers);
	if (philosophers == NULL)
	{
		perror("Failed to allocate memory for philosophers");
		return -1;
	}
	if (num_philosophers == 1)
	{
		one_philosopher(philosophers, data, forks);
		return (0);
	}
	initialize_philosophers_and_forks(philosophers, data, forks, num_philosophers);
	int i = 0;
	while (i < num_philosophers)
	{
		if (pthread_join(philosophers[i].thread, NULL) != 0)
			exit(3);
		i++;
	}
	clean_up(philosophers, data, forks, num_philosophers);
	return (0);
}
