/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 20:15:50 by lhasmi            #+#    #+#             */
/*   Updated: 2023/07/20 04:38:16 by lhasmi           ###   ########.fr       */
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
	long long			end_last_lunch;
	long long			start_last_lunch;
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

void					eating_cycle(t_philosophers *philosophers);
void					sleeping_cycle(t_philosophers *philosophers);
bool					is_philosopher_dead(t_philosophers *philosophers);
void					init_philosophers_and_forks(t_philosophers *philosophers,
							t_data *data, pthread_mutex_t *forks,
							int num_philosophers);

/////////// threads_bis.c  /////////
void					*routine(void *arg);
void					*routine_one(void *arg);
void					philosopher_routine(t_philosophers *philosophers);
void					philosopher_routine_2(t_philosophers *philosophers);
void					process_death(t_philosophers *philosophers, char *msg);
void					thinking_cycle(t_philosophers *philosophers);

/////////// philooutils.c  /////////
void					sync_start(t_philosophers *philosophers);
long long				is_timenow(void);
void					ft_usleep(long time);
void					printing(t_philosophers *philosopher, char *msg);
bool					check_full(t_philosophers *philosophers);

/////////// philoutils_bis.c  /////////
void					check_death(t_philosophers *philosophers);
void					clean_up(t_philosophers *philosophers, t_data *data,
							pthread_mutex_t *forks, int num_philosophers);
void					initialize_philosophers_and_forks(t_philosophers *philosophers,
							t_data *data, pthread_mutex_t *forks,
							int num_philosophers);
void					initialize_mutexes(t_data *data, pthread_mutex_t *forks,
							int num_philosophers);
t_data					*init_data(int argc, char *argv[]);
t_philosophers			*init_philosophers(int num_philosophers);
void					join_threads(t_philosophers *philosophers,
							int num_philosophers);
int						parser(char *argv[], int argc, char ***args);

/////////// libft files  /////////
bool					ft_isint(char *arg);
bool					ft_isnumber(char *str);
size_t					ft_strlen(const char *s);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
int						ft_isdigit(int c);
void					free_argv(char **arr);
char					**ft_split(const char *str, char del);
void					ft_error(char *str);
size_t					ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t					ft_wcount(const char *str, char del);
int						invalid_arg(int j, char **args, char *argv[]);
int						check_input(char *argv[], int argc, char ***args);
void					check_arguments_and_parse(int argc, char *argv[],
							char ***args);
int						ft_isdigit(int c);

#endif
