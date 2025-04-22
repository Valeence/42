/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Analy_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zachamou <zachamou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 04:06:51 by zachamou          #+#    #+#             */
/*   Updated: 2024/06/27 23:27:15 by zachamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/MiniShell.h"

int	fonction_qote(char c, int flag_supp_qote, t_data *data)
{
	if (c == S_QOTES)
	{
		flag_supp_qote = 1;
		data->data2->in_single_quote = !data->data2->in_single_quote;
		data->flag_qote = 1;
	}
	if (c == D_QOTES)
	{
		flag_supp_qote = 1;
		data->data2->in_double_quote = !data->data2->in_double_quote;
		data->flag_qote = 1;
	}
	return (flag_supp_qote);
}

int	shr_not_cmd(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '.' || str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	ft_cont_w(char *s)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != ' ')
		{
			count++;
			while (s[i] && s[i] != ' ')
				i++;
		}
		else
			i++;
	}
	if (count > 2)
		count = 3;
	return (count);
}

void	ft_analy_type_redi_in(t_data *data, t_Token **current)
{
	int	size;

	if (*current == NULL)
		return ;
	(*current)->type = E_IN;
	if ((*current)->next != NULL)
	{
		size = ft_cont_w((*current)->next->token_str);
		if (size > 1)
		{
			insert_nodes_at_current(*current, size);
			(*current)->next->type = E_FILE;
			if ((*current)->next->next != NULL)
				(*current)->next->next->type = E_WORD;
		}
		else
			(*current)->next->type = E_FILE;
		*current = (*current)->next;
		data->data2->nb_file_in += 1;
	}
}

void	ft_analy_type_else(t_data *data, t_Token **current)
{
	if (shr_not_cmd((*current)->token_str) == 1)
		(*current)->type = E_NOT_CMD;
	else
	{
		(*current)->type = E_WORD;
		data->nb_cmd += 1;
	}
}
