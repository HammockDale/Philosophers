/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex02.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdale <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 15:22:05 by hdale             #+#    #+#             */
/*   Updated: 2021/12/25 15:22:08 by hdale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	*ft_kill(void *argv)
{
	t_philo		*philo;
	int			i;

	philo = (t_philo *)argv;
	i = philo->mas->num - 1;
	sem_wait(philo->mas->sem_kill);
	while (i >= 0)
	{
		kill(philo[i].pid, SIGKILL);
		i--;
	}
	ft_sem_free(philo->mas);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_mas	mas;
	t_philo	*philo;

	if (valid_argv(argc, argv) == 1)
		return (1);
	if (init_mas(argc, argv, &mas))
		return (1);
	if (init_philo(&philo, &mas))
		return (1);
	ft_start(philo, mas);
	return (0);
}
