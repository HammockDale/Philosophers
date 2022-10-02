/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isstr_digit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdale <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 15:25:34 by hdale             #+#    #+#             */
/*   Updated: 2021/12/25 15:25:36 by hdale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

int	ft_isstr_digit(char *str)
{
	unsigned char	ch;

	while (*str)
	{
		ch = (unsigned char)*str;
		if (ch < '0' || ch > '9')
		{
			return (1);
		}
		str++;
	}
	return (0);
}
