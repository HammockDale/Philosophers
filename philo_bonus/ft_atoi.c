/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdale <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 15:21:44 by hdale             #+#    #+#             */
/*   Updated: 2021/12/25 15:21:47 by hdale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

int	ft_atoi(const char *str)
{
	int		i;
	int		tmp;
	char	*copy;

	copy = (char *)str;
	i = 1;
	tmp = 0;
	while (*copy != 0 && ((*copy >= 9 && *copy <= 13) || *copy == 32))
		copy++;
	if (*copy == '-')
		i = -i;
	if (*copy == '-' || *copy == '+')
		copy++;
	while (ft_isdigit(*copy))
	{
		if (i > 0)
			tmp = (tmp * 10) + (*copy - '0');
		else
			tmp = (tmp * 10) - (*copy - '0');
		copy++;
	}
	return (tmp);
}
