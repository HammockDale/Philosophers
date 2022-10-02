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

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <string.h>

typedef pthread_mutex_t	t_mutex;

typedef struct d_mas
{
	int				num;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				count;
	int				philo_l_eat;
	char			stop;
	struct timeval	start;
	struct timeval	death;
	pthread_t		death_thread;
	pthread_t		eat_thread;
	pthread_t		kill_thread;
	pthread_t		thread;
	sem_t			*sem;
	sem_t			*sem_print;
	sem_t			*sem_eat;
	sem_t			*sem_kill;
}					t_mas;

typedef struct s_philo
{
	pthread_t		thread;
	pthread_t		death_thread;
	int				num;
	int				count;
	t_mas			*mas;
	struct timeval	start;
	struct timeval	death;
	pid_t			pid;
}					t_philo;

int			ft_isdigit(int c);
int			ft_atoi(const char *str);
int			ft_isstr_digit(char *str);
int			init_mas(int argc, char **argv, t_mas *mas);
int			valid_argv(int argc, char **argv);
int			init_philo(t_philo **philo, t_mas *mas);
long int	ft_usleep(long int time);
void		ft_print_bonus(t_philo *philo, const char *str);
void		ft_sem_free(t_mas *mas);
void		ft_init_sem(t_mas *mas);
void		ft_start(t_philo *philo, t_mas mas);
void		*ft_fin(void *argv);
void		*ft_kill(void *argv);
void		ft_run(t_philo *philo, t_mas mas);
void		*ft_death(void *argv);

#endif
