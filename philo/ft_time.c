/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdale <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 15:35:38 by hdale             #+#    #+#             */
/*   Updated: 2021/12/25 15:35:40 by hdale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

long int	ft_usleep(long int time)
{
	struct timeval		start;
	struct timeval		step;

	gettimeofday(&start, NULL);
	while (1)
	{
		usleep(1000);
		gettimeofday(&step, NULL);
		if ((size_t)(((size_t)(step.tv_sec - start.tv_sec)) * 1000000 +
			((size_t)(step.tv_usec - start.tv_usec))) >= (size_t)time)
			break ;
	}
	return (0);
}

void	ft_print(t_philo *philo, const char *str)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	pthread_mutex_lock(philo->print_mutex);
	if (philo->num > 0)
		printf("%ld %d %s\n", ((now.tv_sec * 1000000 + now.tv_usec)
				- (philo->start.tv_sec * 1000000 + philo->start.tv_usec))
			/ 1000, philo->num, str);
	pthread_mutex_unlock(philo->print_mutex);
}

void	ft_print_die(t_philo *philo, const char *str)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	if (philo->num > 0)
		printf("%ld %d %s\n", ((now.tv_sec * 1000000 + now.tv_usec)
				- (philo->start.tv_sec * 1000000 + philo->start.tv_usec))
			/ 1000, philo->num, str);
}
