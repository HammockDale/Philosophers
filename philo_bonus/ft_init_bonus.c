/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdale <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 03:39:50 by hdale             #+#    #+#             */
/*   Updated: 2021/12/12 03:39:53 by hdale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	ft_sem_free(t_mas *mas)
{
	(void)mas;

	sem_unlink("forks");
	sem_unlink("sforks");
	sem_unlink("eforks");
	sem_unlink("killforks");
	exit(0);
}

int	init_philo(t_philo **philo, t_mas *mas)
{
	int		i;

	i = 0;
	*philo = malloc(sizeof(t_philo) * mas->num);
	if (!*philo)
	{
		printf("Error: can't allocate memory\n");
		return (1);
	}
	memset(*philo, 0, sizeof(t_philo) * mas->num);
	while (i < mas->num)
	{
		(*philo)[i].num = i + 1;
		(*philo)[i].mas = mas;
		(*philo)[i].count = mas->count;
		(*philo)[i].death = mas->start;
		i++;
	}
	return (0);
}

void	ft_init_sem(t_mas *mas)
{
	sem_unlink("forks");
	sem_unlink("sforks");
	sem_unlink("eforks");
	sem_unlink("killforks");
	mas->sem = sem_open("forks", O_CREAT | O_EXCL, 0644, mas->num);
	mas->sem_print = sem_open("sforks", O_CREAT | O_EXCL, 0644, 1);
	if (mas->count > 0)
	mas->sem_eat = sem_open("eforks", O_CREAT | O_EXCL, 0644, 0);
	mas->sem_kill = sem_open("killforks", O_CREAT | O_EXCL, 0644, 0);
	if (mas->sem == SEM_FAILED || mas->sem_print == SEM_FAILED
		|| mas->sem_eat == SEM_FAILED || mas->sem_kill == SEM_FAILED)
	{
		printf("Error: semaphore init\n");
		exit (1);
	}
}

int	init_mas(int argc, char **argv, t_mas *mas)
{
	mas->num = ft_atoi(argv[1]);
	mas->t_die = ft_atoi(argv[2]) * 1000;
	mas->t_eat = ft_atoi(argv[3]) * 1000;
	mas->t_sleep = ft_atoi(argv[4]) * 1000;
	gettimeofday(&mas->start, NULL);
	mas->death = mas->start;
	if (mas->num <= 0 || mas->t_die <= 0
		|| mas->t_eat <= 0 || mas->t_sleep <= 0)
	{
		printf("Error: wrong parameters\n");
		return (1);
	}
	if (argc == 6)
	{
		mas->count = ft_atoi(argv[5]);
		if (mas->count <= 0)
		{
			printf("Error: your argv_i is not correct\n");
			return (1);
		}
	}
	else
		mas->count = -1;
	ft_init_sem(mas);
	return (0);
}

int	valid_argv(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("Error: argc is not correct\n");
		return (1);
	}
	if (ft_isstr_digit(argv[1]) || ft_isstr_digit(argv[2])
		|| ft_isstr_digit(argv[3]) || ft_isstr_digit(argv[4]))
	{
		printf("Error: your argv_i is not digit or less than 0\n");
		return (1);
	}
	if (argc == 6 && ft_isstr_digit(argv[5]))
	{
		printf("Error: your argv_i is not digit or less than 0\n");
		return (1);
	}
	return (0);
}
