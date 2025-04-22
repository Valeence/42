/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tok_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zachamou <zachamou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 04:06:38 by zachamou          #+#    #+#             */
/*   Updated: 2024/06/27 20:59:21 by zachamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/MiniShell.h"

bool	ft_isspace(char c)
{
	if (c == 32 || c == 9)
		return (true);
	return (false);
}

bool	ft_is_del(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}

bool	ft_is_qote(char c)
{
	if (c == '\'' || c == '"')
		return (true);
	return (false);
}

int	skip_begin_spaces_prompt(const char *readline, int start)
{
	while (ft_isspace(readline[start]))
		start++;
	return (start);
}

int	extract_token(const char *readline, int start, char **token, t_data *data)
{
	int	end;
	int	flag_supp_qote;

	end = start;
	flag_supp_qote = 0;
	while (readline[end])
	{
		fonction_qote(readline[end], flag_supp_qote, data);
		if (ft_is_del(readline[end]) && (data->data2->in_single_quote == 1
				|| data->data2->in_double_quote == 1))
			end++;
		if (ft_is_del(readline[end]) && (data->data2->in_single_quote == 0
				|| data->data2->in_double_quote == 0))
			break ;
		end++;
	}
	if (flag_supp_qote == 1)
		*token = ft_strndup(readline + (start), (end) - (start));
	else
		*token = ft_strndup(readline + start, end - start);
	return (end);
}
