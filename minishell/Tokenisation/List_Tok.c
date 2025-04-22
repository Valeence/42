/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List_Tok.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zachamou <zachamou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 04:06:45 by zachamou          #+#    #+#             */
/*   Updated: 2024/06/27 23:27:15 by zachamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/MiniShell.h"

int	ft_size_list_token(t_Token *list_token)
{
	int		i;
	t_Token	*curr;

	i = 0;
	curr = list_token;
	while (curr->next != NULL)
	{
		curr->file = NULL;
		curr = curr->next;
		i++;
	}
	return (i);
}

void	add_token(t_Token **begin, t_Token *new_token)
{
	t_Token	*current;

	if (!*begin)
		*begin = new_token;
	else
	{
		current = *begin;
		while (current->next != NULL)
			current = current->next;
		current->next = new_token;
	}
}

t_Token	*creat_noed_token(char *token)
{
	t_Token	*noed;

	noed = malloc(sizeof(t_Token));
	if (!noed)
		return (NULL);
	noed->token_str = ft_strdup(token);
	noed->file = NULL;
	noed->next = NULL;
	return (noed);
}

void	ft_supp_noed_empy(t_Token **list_tok)
{
	t_Token	*current;
	t_Token	*prev;
	t_Token	*next_node;

	current = *list_tok;
	prev = NULL;
	next_node = NULL;
	while (current != NULL)
	{
		next_node = current->next;
		if (current->type == E_EMPTY)
		{
			if (prev == NULL)
				*list_tok = next_node;
			else
				prev->next = next_node;
			free(current->token_str);
			free(current);
		}
		else
			prev = current;
		current = next_node;
	}
}

void	insert_nodes_at_current(t_Token *current, int size)
{
	int		i;
	char	**str_in;
	t_Token	*last_inserted;
	t_Token	*original_next;
	t_Token	*new_node;

	i = 0;
	str_in = ft_split(current->next->token_str, ' ');
	last_inserted = current;
	original_next = current->next->next;
	while (i < size)
	{
		new_node = malloc(sizeof(t_Token));
		if (new_node == NULL)
			return ;
		new_node->token_str = strdup(str_in[i]);
		new_node->next = last_inserted->next;
		last_inserted->next = new_node;
		last_inserted = new_node;
		i++;
	}
	last_inserted->next = original_next;
	ft_free_tabtab(str_in);
}
