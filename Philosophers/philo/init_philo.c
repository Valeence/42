/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:32:14 by vandre            #+#    #+#             */
/*   Updated: 2024/03/12 08:18:31 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	set_philo(t_data *data, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		pthread_mutex_init(&philo[i].r_fork, NULL);
	}
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&philo[i].mutex_nb_lunch, NULL);
		pthread_mutex_init(&philo[i].mutex_last_eat, NULL);
		philo[i].last_eat = 0;
		philo[i].id = i + 1;
		philo[i].data = data;
		if (i < data->nb_philo - 1)
			philo[i].l_fork = &philo[i + 1].r_fork;
		else
			philo[i].l_fork = &philo[0].r_fork;
		i++;
	}
	return (0);
}

int	create_thread(t_data *data, t_philo *philo)
{
	int	i;

	i = -1;
	data->time_start = get_time();
	while (++i < data->nb_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]) != 0)
			return (1);
	}
	ft_dead(philo, data);
	i = -1;
	while (++i < data->nb_philo)
		pthread_join(philo[i].thread, NULL);
	return (0);
}

int	init_philo(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	if (set_philo(*&data, philo) == 1)
		return (1);
	if (create_thread(data, philo) == 1)
		return (1);
	return (0);
}
