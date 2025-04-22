/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 02:33:54 by vandre            #+#    #+#             */
/*   Updated: 2024/03/12 08:04:26 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	mutex_destroy(t_philo *philo, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		pthread_mutex_destroy(&philo[i].mutex_nb_lunch);
		pthread_mutex_destroy(&philo[i].r_fork);
		pthread_mutex_destroy(&philo[i].mutex_last_eat);
	}
	pthread_mutex_destroy(&data->mutex_death);
	pthread_mutex_destroy(&data->mutex_print);
	pthread_mutex_destroy(&data->mutex_nb_time_eat);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philo;

	if (argc != 5 && argc != 6)
		return (printf("Error\nWrong nb of args"), 1);
	if (check_args(&data, argc, argv))
		return (printf("Error\nInvalid args"), 1);
	philo = ft_calloc(sizeof(t_philo), data.nb_philo);
	if (!philo)
		return (printf("Error\nCalloc"), 1);
	if (init_philo(&data, philo))
		return (printf("Error\nThread problem"), 1);
	mutex_destroy(philo, &data);
	free(philo);
	return (0);
}
