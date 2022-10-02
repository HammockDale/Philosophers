/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdale <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 15:48:59 by hdale             #+#    #+#             */
/*   Updated: 2021/12/25 15:49:01 by hdale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef pthread_mutex_t	t_mutex;

typedef struct d_mas
{
	int				num;
	int				t_die;
	int				t_eat;
	int				count;
	int				t_sleep;
	struct timeval	start;
}					t_mas;

typedef struct d_philo
{
	int				num;
	int				end_eat;
	int				t_die;
	int				t_eat;
	int				die;
	int				count;
	struct timeval	start;
	struct timeval	death;
	int				t_sleep;
	pthread_t		thread_philo;
	pthread_t		death_thread;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	*print_mutex;
}					t_philo;

typedef struct d_var
{
	pthread_t		*philo_thread;
	pthread_t		*death_thread;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	*print_mutex;
	int				num;
	int				ind;
	int				end_eat;
	t_philo			*philo;
	t_mas			*mas;
	pthread_mutex_t	*count_eat;
}					t_var;

void		*ft_memset(void *str, int c, size_t n);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
int			ft_isdigit(int c);
int			ft_atoi(const char *str);
int			ft_isstr_digit(char *str);
int			init_mas(int argc, char **argv, t_mas *mas);
int			valid_argv(int argc, char **argv);
int			malloc_threads_mutexes(t_var *var);
int			init_mutex(t_var *var);
int			init_var(t_var *var, t_mas *mas);
int			init_each_philo(t_mas *mas, t_var *var);
int			create_threads(t_var *var, int num);
void		*philo_routine(void *argv);
void		*deathchecker_routine(void *argv);
void		*print(void *buf);
long int	ft_usleep(long int time);
long int	ft_time(long int time);
int			ft_free_all(t_var *var, t_mas *mas);
void		ft_print(t_philo *philo, const char *str);
void		ft_print_die(t_philo *philo, const char *str);

#endif
