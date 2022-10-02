/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pthread.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdale <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 15:26:09 by hdale             #+#    #+#             */
/*   Updated: 2021/12/25 15:26:12 by hdale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*death_routine(void *argv)
{
	t_var	*var;
	int		i;
	int		k;

	i = 0;
	k = 0;
	var = (t_var *)argv;
	while (var->philo[i].end_eat == 1)
	{
		k++;
		i++;
	}
	if (k == var->mas->num)
		pthread_mutex_lock(var->print_mutex);
	ft_usleep(100000);
	return (NULL);
}

void	*philo_routine(void *argv)
{
	t_philo			*philo;

	philo = (t_philo *)argv;
	if ((philo->num + 1) % 2 == 1)
		ft_usleep(10000);
	while (philo->num > 0)
	{
		pthread_mutex_lock(philo->right);
		ft_print(philo, "has taken a fork");
		pthread_mutex_lock(philo->left);
		ft_print(philo, "has taken a fork");
		ft_print(philo, "is eating");
		ft_usleep(philo->t_eat);
		philo->count--;
		gettimeofday(&philo->death, NULL);
		ft_print(philo, "is sleeping");
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
		ft_usleep(philo->t_sleep);
		ft_print(philo, "is thinking");
	}
	return (NULL);
}

void	*philo_life(void *argv)
{
	t_philo			*philo;
	struct timeval	now;

	philo = (t_philo *)argv;
	while (philo->num > 0)
	{
		pthread_mutex_lock(philo->print_mutex);
		gettimeofday(&now, NULL);
		if (((now.tv_sec * 1000000 + now.tv_usec) - (philo->death.tv_sec
					* 1000000 + philo->death.tv_usec))
			>= (long int) philo->t_die)
		{
			philo->die = 1;
			ft_print_die(philo, "died");
			return (NULL);
		}
		pthread_mutex_unlock(philo->print_mutex);
		ft_usleep(1000);
	}
	return (NULL);
}

int	create_threads(t_var *var, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		if (pthread_create(&var->philo[i].thread_philo, NULL,
				philo_routine, (void *)(&(var->philo[i]))))
			return (1);
		if (pthread_create(&var->philo[i].death_thread, NULL,
				philo_life, (void *)(&(var->philo[i]))))
			return (1);
		i++;
	}
	i = 0;
	while (i < num)
	{
		if (pthread_detach(var->philo[i].thread_philo))
			return (1);
		if (pthread_detach(var->philo[i].death_thread))
			return (1);
		i++;
	}
	return (0);
}
