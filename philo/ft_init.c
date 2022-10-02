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

#include <philo.h>

int	init_each_philo(t_mas *mas, t_var *var)
{
	int	i;

	i = 0;
	while (i < mas->num)
	{
		var->philo[i].num = i + 1;
		var->philo[i].die = 0;
		var->philo[i].t_eat = mas->t_eat;
		var->philo[i].t_die = mas->t_die;
		var->philo[i].t_sleep = mas->t_sleep;
		var->philo[i].count = mas->count;
		var->philo[i].left = &(var->forks_mutex[i]);
		var->philo[i].right = &(var->forks_mutex[(i + 1) % mas->num]);
		var->philo[i].print_mutex = var->print_mutex;
		var->philo[i].start = mas->start;
		var->philo[i].death = mas->start;
		var->philo[i].end_eat = 0;
		i++;
	}
	return (0);
}

int	init_var(t_var *var, t_mas *mas)
{
	var->num = mas->num;
	if (malloc_threads_mutexes(var) == 1)
		return (1);
	init_mutex(var);
	var->end_eat = 0;
	var->philo = ft_calloc(sizeof(t_philo), (mas->num + 1));
	if (var->philo == NULL)
		return (1);
	init_each_philo(mas, var);
	return (0);
}

int	init_mas(int argc, char **argv, t_mas *mas)
{
	if (valid_argv(argc, argv) == 1)
		return (1);
	mas->num = ft_atoi(argv[1]);
	mas->t_die = ft_atoi(argv[2]) * 1000;
	mas->t_eat = ft_atoi(argv[3]) * 1000;
	mas->t_sleep = ft_atoi(argv[4]) * 1000;
	gettimeofday(&mas->start, NULL);
	if (mas->num <= 0 || mas->t_die <= 0
		|| mas->t_eat <= 0 || mas->t_sleep <= 0)
	{
		printf("Error: wrong parameters\n");
		return (1);
	}
	if (argc == 6)
	{
		mas->count = ft_atoi(argv[5]);
		if (mas->count < 0)
		{
			printf("Error: your argv_i is not correct\n");
			return (1);
		}
	}
	else
		mas->count = -1;
	return (0);
}

int	malloc_threads_mutexes(t_var *var)
{
	var->philo_thread = (pthread_t *)malloc(sizeof(pthread_t));
	if (var->philo_thread == NULL)
		return (1);
	var->death_thread = (pthread_t *)malloc(sizeof(pthread_t));
	if (var->death_thread == NULL)
		return (1);
	var->forks_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* (var)->num);
	if (var->forks_mutex == NULL)
		return (1);
	var->count_eat = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (var->count_eat == NULL)
		return (1);
	var->print_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (var->print_mutex == NULL)
		return (1);
	return (0);
}

int	init_mutex(t_var *var)
{
	int	i;

	i = 0;
	while (i < var->num)
	{
		pthread_mutex_init(&(var->forks_mutex[i]), NULL);
		++i;
	}
	pthread_mutex_init(var->print_mutex, NULL);
	pthread_mutex_init(var->count_eat, NULL);
	return (0);
}
