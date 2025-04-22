/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 02:33:19 by vandre            #+#    #+#             */
/*   Updated: 2024/02/01 03:02:41 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int	check_argv(char	*str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	if (str[i] == '-' || (str[i] >= '0' && str[i] <= '9'))
	{
		i++;
		if (str[0] == '-' && str[1] == '\0')
			return (1);
		while (str[i])
		{
			if (!ft_isdigit(str[i]))
				return (1);
			i++;
		}
	}
	else
		return (1);
	return (0);
}

int	check_duplicate(t_stack*stack_a, int nb)
{
	if (!stack_a)
		return (0);
	while (stack_a)
	{
		if ((stack_a)->value == nb)
			return (1);
		stack_a = (stack_a)->next;
	}
	return (0);
}

void	free_stack(t_stack**stack_a, t_stack**stack_b)
{
	t_stack	*tmp;

	if (!stack_a || !stack_b)
		return ;
	while (*stack_a)
	{
		tmp = (*stack_a)->next;
		free(*stack_a);
		*stack_a = tmp;
	}
	while (*stack_b)
	{
		tmp = (*stack_b)->next;
		free(*stack_b);
		*stack_b = tmp;
	}
}

void	free_sa(t_stack**stack_a)
{
	t_stack	*tmp;

	if (!stack_a)
		return ;
	while (*stack_a)
	{
		tmp = (*stack_a)->next;
		free(*stack_a);
		*stack_a = tmp;
	}
	ft_printf("Error\n");
}

void	free_argv(char **argv, int j)
{
	int	i;

	i = 0;
	if (!argv)
		return ;
	if (j == 1)
		return ;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}
