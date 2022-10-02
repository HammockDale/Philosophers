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

#include <philo_bonus.h>

long int	ft_usleep(long int time)
{
	struct timeval		start;
	struct timeval		step;
	unsigned long long	l;

	l = 0;
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

void	ft_print_bonus(t_philo *philo, const char *str)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	sem_wait(philo->mas->sem_print);
	printf("%-8ld philo %d %s\n", ((now.tv_sec * 1000000 + now.tv_usec)
			- (philo->mas->start.tv_sec * 1000000 + philo->mas->start.tv_usec))
		/ 1000, philo->num, str);
	sem_post(philo->mas->sem_print);
}
