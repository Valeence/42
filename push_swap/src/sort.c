/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:50:19 by vandre            #+#    #+#             */
/*   Updated: 2024/02/01 14:43:21 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int	get_bit_max_list(t_stack **stack_a)
{
	t_stack		*current;
	int			max_num;
	int			max_bits;

	current = *stack_a;
	max_num = current->lindex;
	while (current)
	{
		if (current->lindex > max_num)
			max_num = current->lindex;
		current = current->next;
	}
	max_bits = 0;
	while ((max_num >> max_bits) != 0)
		max_bits++;
	return (max_bits);
}

void	radix_sort_bit(t_stack **stack_a,
						t_stack **stack_b,
						int bit_pos)
{
	t_stack		*current;
	int			i;
	int			size;

	i = 0;
	size = stack_len(*stack_a);
	while (i < size)
	{
		current = *stack_a;
		if (((current->lindex >> bit_pos) & 1) == 0)
			pb(stack_a, stack_b);
		else
			ra(stack_a);
		i++;
	}
	while (stack_len(*stack_b) != 0)
		pa(stack_a, stack_b);
}

void	radix_sort(t_stack **stack_a, t_stack **stack_b)
{
	int	i;
	int	max_bits;

	i = 0;
	if (is_sorted(stack_a))
		return ;
	max_bits = get_bit_max_list(stack_a);
	while (i < max_bits)
	{
		radix_sort_bit(stack_a, stack_b, i);
		i++;
	}
}
