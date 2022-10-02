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

#include <philo.h>

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

static int	ft_while(t_var *var, t_mas *mas)
{
	int	i;
	int	k;

	while (1)
	{
		ft_usleep(100);
		pthread_mutex_lock(var->count_eat);
		k = 0;
		i = 0;
		while (i < mas->num)
		{
			if (var->philo[i].die == 1)
				return (0);
			if (mas->count >= 0 && var->philo[i].count <= 0)
				k++;
			i++;
		}
		if (k == mas->num)
		{
			return (0);
		}
		pthread_mutex_unlock(var->count_eat);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_mas	mas;
	t_var	var;

	if (init_mas(argc, argv, &mas))
		return (1);
	if (init_var(&var, &mas))
		return (1);
	if (create_threads(&var, mas.num))
		return (1);
	ft_while(&var, &mas);
	ft_free_all(&var, &mas);
	return (0);
}
