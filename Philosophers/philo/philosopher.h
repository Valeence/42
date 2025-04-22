/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 02:34:09 by vandre            #+#    #+#             */
/*   Updated: 2024/03/12 08:07:41 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>

typedef struct data
{
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_time_eat;
	long int		time_start;
	int				died;
	int				nb_eat;
	pthread_mutex_t	mutex_death;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_nb_time_eat;
}		t_data;

typedef struct philo
{
	pthread_t		thread;
	t_data			*data;
	int				id;
	int				last_eat;
	int				nb_lunch;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	r_fork;
	pthread_mutex_t	mutex_nb_lunch;
	pthread_mutex_t	mutex_last_eat;
}		t_philo;

int			check_args(t_data *data, int argc, char **argv);
int			ft_atoi(const char *str);
int			init_philo(t_data *data, t_philo *philo);
void		*routine(void *arg);
long int	get_time(void);
void		ft_usleep(long int usleeep, t_philo *philo, t_data *data);
int			print(t_philo *philo, char *str, t_data *data);
int			ft_check_meals(t_philo *philo);
void		ft_odd(t_data *data);
int			return_data_died(t_philo *philo);
void		*single_philo(t_philo *philo, t_data *data);
void		*ft_calloc(size_t count, size_t size);
int			mut_lock_l(t_philo *philo, t_data *data);
int			mut_lock_r(t_philo *philo, t_data *data);
int			ft_dead(t_philo *philo, t_data *data);
int			ft_death(t_data *data);
int			ft_check_death(t_philo *philo, int i, t_data *data);
void		debug_print(t_philo *philo, t_data *data);
void		check_nbeat(t_philo	*philo, t_data *data);

#endif