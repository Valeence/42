/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 03:55:38 by vandre            #+#    #+#             */
/*   Updated: 2024/03/12 08:31:32 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	mut_lock_l(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(philo->l_fork);
	if (print(philo, "has taken a fork", data) != 1)
	{
		pthread_mutex_unlock(philo->l_fork);
		return (0);
	}
	pthread_mutex_lock(&philo->r_fork);
	if (print(philo, "has taken a fork", data) != 1)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(&philo->r_fork);
		return (0);
	}
	return (1);
}

int	mut_lock_r(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&philo->r_fork);
	if (print(philo, "has taken a fork", data) != 1)
	{
		pthread_mutex_unlock(&philo->r_fork);
		return (0);
	}
	pthread_mutex_lock(philo->l_fork);
	if (print(philo, "has taken a fork", data) != 1)
	{
		pthread_mutex_unlock(&philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return (0);
	}
	return (1);
}

void	*single_philo(t_philo *philo, t_data *data)
{
	ft_usleep(philo->data->time_die, philo, data);
	return (NULL);
}

int	print(t_philo *philo, char *str, t_data *data)
{
	if (ft_death(data) && strcmp(str, "died") != 0)
		return (0);
	pthread_mutex_lock(&data->mutex_print);
	printf("%ld %d %s\n", get_time() - philo->data->time_start, philo->id, str);
	pthread_mutex_unlock(&data->mutex_print);
	return (1);
}
