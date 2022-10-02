/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdale <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 15:22:29 by hdale             #+#    #+#             */
/*   Updated: 2021/12/25 15:22:35 by hdale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	un_malloc_threads_mutexes(t_var *var)
{
	free(var->philo_thread);
	free(var->death_thread);
	free(var->forks_mutex);
	free(var->count_eat);
	free(var->print_mutex);
	return (0);
}

int	ft_free_all(t_var *var, t_mas *mas)
{
	(void)mas;
	free(var->philo);
	un_malloc_threads_mutexes(var);
	return (0);
}
