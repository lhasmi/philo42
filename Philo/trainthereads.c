/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trainthereads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 20:00:27 by lhasmi            #+#    #+#             */
/*   Updated: 2023/07/13 20:33:42 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *myturn(void *arg)
{
	int *p = (int *)arg;
	int i = 0;
	while(i < 8)
	{
		sleep(1);
		printf("My Turn! %d %d\n", i, *p);
		(*p)++;
		i++;
	}
	return NULL;
}

void yourturn()
{
	while(2)
	{
		sleep(2);
		printf("Your Turn!\n");
	}
}

//without thread mytun runs forever the other never gets to run
int	main()
{
	pthread_t newthread;
	int i = 5;

	pthread_create(&newthread, NULL, &myturn, &i);
	yourturn();
	pthread_join(newthread, NULL);
	printf("Threads done :i=%d\n", i);
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
