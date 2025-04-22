/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokenisaton.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zachamou <zachamou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 04:15:21 by zachamou          #+#    #+#             */
/*   Updated: 2024/06/28 00:31:06 by zachamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/MiniShell.h"

void	ft_analy_type(t_data *data, t_Token **list_tok)
{
	t_Token	*current;

	current = *list_tok;
	while (current != NULL)
	{
		if (strcmp(current->token_str, PIP) == 0)
			ft_analy_type_pipe(&current);
		else if (strcmp(current->token_str, RDI_IN) == 0)
			ft_analy_type_redi_in(data, &current);
		else if (strcmp(current->token_str, RDI_OUT) == 0)
			ft_analy_type_redi_out(&current, data);
		else if (strcmp(current->token_str, ">>") == 0)
			ft_analy_type_redi_append(&current, data);
		else if (strcmp(current->token_str, "<<") == 0)
			ft_analy_type_redi_heredoc(&current);
		else if (strcmp(current->token_str, "\0") == 0
			|| strcmp(current->token_str, "") == 0)
			current->type = E_EMPTY;
		else
			ft_analy_type_else(data, &current);
		if (current != NULL)
			current = current->next;
	}
}

void	pre_add_special_tok(const char *readline, t_Token **list_token)
{
	char	*token;
	t_Token	*temp_token;

	token = NULL;
	temp_token = NULL;
	token = ft_strndup(readline, 2);
	temp_token = creat_noed_token(token);
	add_token(list_token, temp_token);
	free(token);
}

int	handle_special_tok(const char *readline, t_Token **list_token, int i)
{
	char	*token;
	t_Token	*temp_token;

	token = NULL;
	temp_token = NULL;
	if (readline[i] == '>' && readline[i + 1] == '>')
	{
		pre_add_special_tok(&readline[i], list_token);
		i += 2;
	}
	else if (readline[i] == '<' && readline[i + 1] == '<')
	{
		pre_add_special_tok(&readline[i], list_token);
		i += 2;
	}
	else
	{
		token = ft_strndup(&readline[i], 1);
		temp_token = creat_noed_token(token);
		add_token(list_token, temp_token);
		free(token);
		i++;
	}
	return (i);
}

void	ft_tokenize_moi_ca(const char *readline, t_Token **list_token,
		t_data *data)
{
	int		i;
	char	*token;
	t_Token	*temp_token;

	i = 0;
	token = NULL;
	temp_token = NULL;
	while (readline[i])
	{
		if (ft_isspace(readline[i]))
		{
			i++;
			continue ;
		}
		i = extract_token(readline, i, &token, data);
		temp_token = creat_noed_token(token);
		add_token(list_token, temp_token);
		free(token);
		if (ft_is_del(readline[i]))
			i = handle_special_tok(readline, list_token, i);
	}
}

void	ft_lexer(t_data *data, t_Token **list_token)
{
	ft_tokenize_moi_ca(data->pronpt, list_token, data);
	ft_analy_type(data, list_token);
	ft_supp_noed_empy(list_token);
}
