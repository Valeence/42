/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:12:38 by vandre            #+#    #+#             */
/*   Updated: 2024/03/12 08:08:12 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;
	size_t			i;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		*p = 0;
		i++;
		p++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	total;

	total = count * size;
	if (count != 0 && total / count != size)
		return (NULL);
	ptr = (void *)malloc(total);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, total);
	return (ptr);
}

long int	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return ((time.tv_sec) * 1000 + (time.tv_usec) / 1000);
}

void	ft_usleep(long int usleeep, t_philo *philo, t_data *data)
{
	long int	time;

	(void)philo;
	time = get_time();
	while (get_time() - time < usleeep)
	{
		if (ft_death(data) == 1)
			return ;
		usleep(10);
	}
}
