/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:09:14 by vandre            #+#    #+#             */
/*   Updated: 2024/03/12 07:27:51 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	sleeping(t_philo *philo, t_data *data)
{
	if (print(philo, "is sleeping", data) != 1)
		return (0);
	ft_usleep(philo->data->time_sleep, philo, data);
	return (1);
}

int	think(t_philo *philo, t_data *data)
{
	if (print(philo, "is thinking", data) != 1)
		return (0);
	return (1);
}

int	ft_eat(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&philo->mutex_last_eat);
	philo->last_eat = (get_time() - data->time_start);
	pthread_mutex_unlock(&philo->mutex_last_eat);
	pthread_mutex_lock(&philo->mutex_nb_lunch);
	philo->nb_lunch++;
	check_nbeat(philo, data);
	pthread_mutex_unlock(&philo->mutex_nb_lunch);
	if (print(philo, "is eating", data) != 1)
		return (0);
	ft_usleep(philo->data->time_eat, philo, data);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(&philo->r_fork);
	}
	if (philo->id % 2 == 1)
	{
		pthread_mutex_unlock(&philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
	return (1);
}

int	eat(t_philo *philo, t_data *data)
{
	if (philo->id % 2 == 0)
	{
		if (mut_lock_l(philo, data) != 1)
			return (0);
		if (ft_eat(philo, data) != 1)
			return (0);
	}
	else if (philo->id % 2 == 1)
	{
		if (mut_lock_r(philo, data) != 1)
			return (0);
		if (ft_eat(philo, data) != 1)
			return (0);
	}
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nb_philo == 1)
		return (single_philo(philo, philo->data));
	if (philo->id % 2 == 0)
		ft_usleep((philo->data->time_eat), philo, philo->data);
	while (ft_death(philo->data) != 1)
	{
		if (!eat(philo, philo->data))
			break ;
		if (!sleeping(philo, philo->data))
			break ;
		if (!think(philo, philo->data))
			break ;
		if (philo->data->nb_philo % 2)
			ft_odd(philo->data);
	}
	return (NULL);
}
