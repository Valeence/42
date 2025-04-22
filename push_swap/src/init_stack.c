/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:25:57 by vandre            #+#    #+#             */
/*   Updated: 2024/02/01 14:39:02 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	append_node(t_stack**stack_a, int nb)
{
	t_stack	*node;
	t_stack	*last_node;

	if (!stack_a)
		return ;
	node = malloc(sizeof(t_stack));
	if (!node)
		return ;
	node->next = NULL;
	node->value = nb;
	if (!(*stack_a))
	{
		*stack_a = node;
		node->prev = NULL;
	}
	else
	{
		last_node = find_last(*stack_a);
		last_node->next = node;
		node->prev = last_node;
	}
}

void	init_stack_a(t_stack**stack_a, char **argv, int i)
{
	int	nb;
	int	j;

	j = i;
	while (argv[i])
	{
		if (check_argv(argv[i]))
			return (free_argv(argv, j), free_sa(stack_a), exit(1));
		if (!ft_atoi(argv[i], &nb))
			return (free_argv(argv, j), free_sa(stack_a), exit(1));
		if (check_duplicate(*stack_a, nb))
			return (free_argv(argv, j), free_sa(stack_a), exit(1));
		append_node(stack_a, nb);
		i++;
	}
	free_argv(argv, j);
	get_index(stack_a);
}
