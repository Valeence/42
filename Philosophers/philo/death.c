/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 03:36:25 by vandre            #+#    #+#             */
/*   Updated: 2024/03/12 08:07:33 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_all_ate(t_data *data)
{
	pthread_mutex_lock(&data->mutex_nb_time_eat);
	if (data->nb_eat == data->nb_philo)
	{
		pthread_mutex_unlock(&data->mutex_nb_time_eat);
		pthread_mutex_lock(&data->mutex_death);
		data->died = 1;
		pthread_mutex_unlock(&data->mutex_death);
		return (1);
	}
	pthread_mutex_unlock(&data->mutex_nb_time_eat);
	return (0);
}

int	ft_check_death(t_philo *philo, int i, t_data *data)
{
	int	r;

	pthread_mutex_lock(&philo[i].mutex_last_eat);
	r = get_time() - data->time_start - philo[i].last_eat;
	pthread_mutex_unlock(&philo[i].mutex_last_eat);
	if (r >= data->time_die)
	{
		pthread_mutex_lock(&data->mutex_death);
		data->died = 1;
		pthread_mutex_unlock(&data->mutex_death);
		print(&philo[i], "died", data);
		return (1);
	}
	return (0);
}

int	ft_dead(t_philo *philo, t_data *data)
{
	int		i;

	i = 0;
	while (!ft_death(data))
	{
		while (i < data->nb_philo)
		{
			if (check_all_ate(data))
				return (1);
			if (ft_check_death(philo, i, data) == 1)
				return (1);
			i++;
		}
		i = 0;
		usleep(500);
	}
	return (0);
}

int	ft_death(t_data *data)
{
	int	z;

	pthread_mutex_lock(&data->mutex_death);
	z = data->died;
	pthread_mutex_unlock(&data->mutex_death);
	return (z);
}
