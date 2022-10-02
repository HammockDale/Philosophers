/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monitor_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdale <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 16:10:06 by hdale             #+#    #+#             */
/*   Updated: 2022/01/29 16:10:11 by hdale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	*ft_death(void *argv)
{
	t_philo				*philo;
	struct timeval		now;
	struct timeval		start;

	philo = (t_philo *)argv;
	start = philo->mas->start;
	while (1)
	{
		sem_wait(philo->mas->sem_print);
		gettimeofday(&now, NULL);
		if (((now.tv_sec * 1000000 + now.tv_usec) - (philo->mas->death.tv_sec
					* 1000000 + philo->mas->death.tv_usec)) > philo->mas->t_die)
		{
			printf("%-8ld philo %d %s\n", ((now.tv_sec * 1000000 + now.tv_usec)
					- (start.tv_sec * 1000000 + start.tv_usec)) / 1000,
				philo->num, "is die");
			sem_post(philo->mas->sem_kill);
			return (NULL);
		}
		sem_post(philo->mas->sem_print);
		usleep(100);
	}
	return (NULL);
}

static void	ft_fin_count(t_philo *philo, t_mas mas)
{
	philo->count--;
	if (philo->count == 0)
	{
		sem_post(philo->mas->sem_eat);
		sem_post(mas.sem);
		sem_post(mas.sem);
		pthread_join(philo->death_thread, NULL);
		exit(0);
	}
}

void	ft_run(t_philo *philo, t_mas mas)
{
	if ((philo->num + 1) % 2 == 1)
		ft_usleep(100);
	while (1)
	{
		sem_wait(mas.sem);
		ft_print_bonus(philo, "has taken right fork");
		sem_wait(mas.sem);
		ft_print_bonus(philo, "has taken left fork");
		ft_print_bonus(philo, "is eating");
		gettimeofday(&philo->mas->death, NULL);
		ft_usleep(philo->mas->t_eat);
		ft_fin_count(philo, mas);
		ft_print_bonus(philo, "is sleeping");
		sem_post(mas.sem);
		sem_post(mas.sem);
		ft_usleep(philo->mas->t_sleep);
		ft_print_bonus(philo, "is thinking");
	}
	exit(0);
}

void	*ft_fin(void *argv)
{
	t_philo			*philo;
	int				i;
	struct timeval	now;

	philo = (t_philo *)argv;
	usleep(10);
	i = 0;
	if (philo->mas->count > 0)
	{
		while (i != philo->mas->num)
		{
			sem_wait(philo->mas->sem_eat);
			i++;
			usleep(1000);
		}
		gettimeofday(&now, NULL);
		sem_post(philo->mas->sem_kill);
	}
	return (NULL);
}

void	ft_start(t_philo *philo, t_mas mas)
{
	int	i;

	i = 0;
	while (i < mas.num)
	{
		philo[i].pid = fork();
		if (philo[i].pid < 0)
			exit(1);
		if (philo[i].pid == 0)
		{
			pthread_create(&philo[i].death_thread, NULL, ft_death,
				(void *)philo);
			ft_run(&philo[i], mas);
			pthread_join(philo[i].death_thread, NULL);
			exit(1);
		}
		i++;
	}
	pthread_create(&philo->thread, NULL, ft_kill, (void *)philo);
	pthread_create(&mas.eat_thread, NULL, ft_fin, (void *)philo);
	pthread_join(philo->thread, NULL);
	pthread_detach(mas.eat_thread);
	exit (0);
}
