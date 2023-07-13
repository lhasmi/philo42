/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 20:00:27 by lhasmi            #+#    #+#             */
/*   Updated: 2023/07/13 22:06:51 by lhasmi           ###   ########.fr       */
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

void	*routine(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
	while (philosopher->meals_eaten != philosopher->meals_required)
	{
		// check flag data.dead
		// print eating (print function has calls is_timenow)
		// call usleep
		// check flag data.dead
		// print sleeping or thinking (print function has calls is_timenow)
		// call usleep

	}
	return NULL;
}

int	main(int argc, char *argv[])
{
	int num_philosophers = atoi(argv[1]);
	pthread_mutex_t	forks[num_philosophers];
	t_philosopher	philosophers[num_philosophers];
	int i = 0;
	if (argc < 5)
	{
		printf("Arguments: number_of_philosophers, time_to_die, time_to_eat, time_to_sleep, [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}

	while ( i < num_philosophers)
	{
		pthread_mutex_init(&forks[i], NULL);
		++i;
	}
	i = 0;
	while (i < num_philosophers)
	{
		philosophers[i].id = i;
		philosophers[i].time_to_die = atoi(argv[2]);
		philosophers[i].time_to_eat = atoi(argv[3]);
		philosophers[i].time_to_sleep = atoi(argv[4]);
		philosophers[i].meals_required = (argc == 6) ? atoi(argv[5]) : -1;
		philosophers[i].left_fork = &forks[i];
		philosophers[i].right_fork = &forks[(i + 1) % num_philosophers];
		if (pthread_create(&philosophers[i].thread, NULL, &routine,
				&philosophers[i]) != 0)
			return (2);
		++i;
	}
	i = 0;
	while (i < num_philosophers)
	{
		if (pthread_join(philosophers[i].thread, NULL) != 0)
			return (3);
		++i;
	}
	i = 0;
	while (i < num_philosophers)
	{
		pthread_mutex_destroy(&forks[i]);
		++i;
	}
	return (0);
}

// int	main(int argc, char *argv[])
// {
// 	int	number_of_philosophers;
// 	t_philosopher

// 	if (argc < 5)
// 	{
// 		printf("Arguments: number_of_philosophers, time_to_die, time_to_eat,
// 				time_to_sleep, number_of_times_each_philosopher_must_eat\n");
// 		return (1);
// 	}
// 	pthread_mutex_init(&mutex, NULL);
// 	if (pthread_create(&p1, NULL, &routine, NULL) != 0)
// 		return (1);
// 	if (pthread_create(&p2, NULL, &routine, NULL) != 0)
// 		return (2);
// 	// if (pthread_create(&p3, NULL, &routine, NULL) != 0)
// 	//     return (3);
// 	// if (pthread_create(&p4, NULL, &routine, NULL) != 0)
// 	//     return (4);
// 	if (pthread_join(p1, NULL) != 0)
// 		return (5);
// 	if (pthread_join(p2, NULL) != 0)
// 		return (6);
// 	// if (pthread_join(p3, NULL) != 0)
// 	//     return (7);
// 	// if (pthread_join(p4, NULL) != 0)
// 	//     return (8);
// 	pthread_mutex_destroy(&mutex);
// 	printf("Number of mails: %d\n", mails);
// 	return (0);
// }

//in a loop

// int mails = 0;
// pthread_mutex_t mutex;

// void* routine() {
//     for (int i = 0; i < 10000000; i++) {
//         pthread_mutex_lock(&mutex);
//         mails++;
//         pthread_mutex_unlock(&mutex);
//     }
// }

// int main(int argc, char* argv[]) {
//     pthread_t th[8];
//     int i;
//     pthread_mutex_init(&mutex, NULL);
//     for (i = 0; i < 8; i++) {
//         if (pthread_create(th + i, NULL, &routine, NULL) != 0) {
//             perror("Failed to create thread");
//             return (1);
//         }
//         printf("Thread %d has started\n", i);
//     }
//     for (i = 0; i < 8; i++) {
//         if (pthread_join(th[i], NULL) != 0) {
//             return (2);
//         }
//         printf("Thread %d has finished execution\n", i);
//     }
//     pthread_mutex_destroy(&mutex);
//     printf("Number of mails: %d\n", mails);
//     return (0);
// }
