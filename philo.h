/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 20:15:50 by lhasmi            #+#    #+#             */
/*   Updated: 2023/07/23 20:44:06 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <ctype.h>
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef struct s_philosophers
{
	int					id;
	long long			last_time_to_eat;
	int					nb_eat;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_data				*data;
}						t_philosophers;

typedef struct s_data
{
	t_philosophers		*philos;
	bool				dead;
	long long			time_to_die;
	long long			time_to_eat;
	long long			time_to_sleep;
	int					meals_required;
	int					num_philosophers;
	long long			start;
	bool				initialized;
	pthread_mutex_t		write;
	pthread_mutex_t		dead_mutex;
	pthread_mutex_t		eat_mutex;
	pthread_mutex_t		init_mutex;
}						t_data;

typedef struct s_philosopher_params
{
	int					id;
	t_data				*data;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
}						t_philosopher_params;

/////////// init.c  /////////
t_data					*init_data(int argc, char **argv);
t_philosophers			*malloc_philosophers(int num_philosophers);
void					initialize_mutexes(t_data *data, pthread_mutex_t *forks,
							int num_philosophers);
int					initialize_philosophers(t_philosophers *philosophers,
							t_data *data, pthread_mutex_t *forks,
							int num_philosophers);
void					init_philos_and_forks(t_philosophers *philosophers,
							t_data *data, pthread_mutex_t *forks,
							int num_philosophers);

/////////// init_bis.c  /////////
void					initialize_philosopher(t_philosophers *philosopher,
							t_philosopher_params params);
int						create_philosopher_thread(t_philosophers *philosopher,
							int num_philosophers);
int						initialize_philosophers(t_philosophers *philosophers,
							t_data *data, pthread_mutex_t *forks,
							int num_philosophers);

/////////// routines.c  /////////
void					eating_cycle(t_philosophers *philosophers);
void					eating_cycle2(t_philosophers *philosophers);
void					sleeping_cycle(t_philosophers *philosophers);
void					thinking_cycle(t_philosophers *philosophers);
bool					is_philosopher_dead(t_philosophers *philosophers);

/////////// threads_bis.c  /////
void					*routine(void *arg);
void					*routine_one(void *arg);
void					thinking_for_odds(t_philosophers *philosophers);
void					philosopher_routine(t_philosophers *philosophers);
void					process_death(t_philosophers *philosophers, char *msg);

/////////// routines2.c  /////////
void					philosopher_routine(t_philosophers *philosophers);
void					philo_eat_sleep_think2(t_philosophers *philosophers);
void					philo_eat_sleep_die2(t_philosophers *philosophers);
void					philosopher_routine_2(t_philosophers *philosophers);

/////////// philooutils.c  /////////
bool					check_full(t_philosophers *philosophers);
void					sync_start(t_philosophers *philosophers);
long long				is_timenow(void);
void					ft_usleep(long time);
int						printing(t_philosophers *philosopher, char *msg);

/////////// philoutils_bis.c  /////////
int						is_digit(int c);
int						is_space(char c);
long long				ft_atoll(const char *str);
void					check_death(t_philosophers *philosophers);
void					clean_up(t_philosophers *philosophers, t_data *data,
							pthread_mutex_t *forks, int num_philosophers);

/////////// libft files  //////////////
bool					ft_isint(char *arg);
bool					ft_isnumber(char *str);
size_t					ft_strlen(const char *s);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
int						ft_isdigit(int c);
int						ft_atoi(const char *str);

/////////// main.c  /////////
void					join_threads(t_philosophers *philosophers,
							int num_philosophers);
int						is_input_error(char **s, int arg_count);
int						check_arguments_and_parse(int argc, char **argv);

#endif
