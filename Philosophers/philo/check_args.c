/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 01:19:27 by vandre            #+#    #+#             */
/*   Updated: 2024/03/12 08:02:51 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_intmax(t_data *data)
{
	if (data->nb_philo < 1 || data->nb_philo > INT_MAX)
		return (1);
	else if (data->time_die < 1 || data->time_die > INT_MAX)
		return (1);
	else if (data->time_eat < 1 || data->time_eat > INT_MAX)
		return (1);
	else if (data->time_sleep < 1 || data->time_sleep > INT_MAX)
		return (1);
	else if (data->time_eat < 1 || data->nb_time_eat > INT_MAX)
		return (1);
	else if (data->nb_time_eat == -1)
		return (0);
	else if (data->nb_time_eat < 1 || data->nb_time_eat > INT_MAX)
		return (1);
	return (0);
}

int	ft_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	check_isdigit(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_digit(argv[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_args(t_data *data, int argc, char **argv)
{
	if (check_isdigit(argv))
		return (1);
	if (argc == 5)
		data->nb_time_eat = -1;
	else if (argc == 6)
	{
		data->nb_time_eat = ft_atoi(argv[5]);
	}
	data->time_start = get_time();
	data->nb_philo = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	data->died = 0;
	data->nb_eat = 0;
	pthread_mutex_init(&data->mutex_death, NULL);
	pthread_mutex_init(&data->mutex_print, NULL);
	pthread_mutex_init(&data->mutex_nb_time_eat, NULL);
	if (check_intmax(data) == 1)
		return (1);
	return (0);
}

void	check_nbeat(t_philo	*philo, t_data *data)
{
	if (philo->nb_lunch == data->nb_time_eat)
	{
		pthread_mutex_lock(&data->mutex_nb_time_eat);
		data->nb_eat++;
		pthread_mutex_unlock(&data->mutex_nb_time_eat);
	}
}
