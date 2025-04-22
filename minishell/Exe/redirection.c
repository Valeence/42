/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zachamou <zachamou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 03:22:02 by zachamou          #+#    #+#             */
/*   Updated: 2024/06/28 00:58:34 by zachamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/MiniShell.h"

void	ft_no_patch(t_data *data)
{
	ft_printf(2, "Bash : command not foundx : %s\n", data->cmd[0]);
	ft_free_tabtab(data->cmd);
	ft_free_tabtab(data->envp);
	free(data->home);
	free(data->path_exe);
	free_token(data->list_token_tmp);
	free(data->data2);
	exit(127);
}

bool	verif_pipe(t_Token *curr)
{
	t_Token	*shr_pipe;

	shr_pipe = curr;
	while (shr_pipe != NULL && shr_pipe->next != NULL)
	{
		if (shr_pipe->next->token_str[0] == '|')
			return (true);
		shr_pipe = shr_pipe->next;
	}
	return (false);
}

void	copy_string(char **dest, const char *src, int index)
{
	int	length;

	length = strlen(src);
	dest[index] = malloc((length + 1) * sizeof(char));
	if (!dest[index])
		exit(EXIT_FAILURE);
	strcpy(dest[index], src);
}

int	count_strings(char **src)
{
	int	count;

	count = 0;
	while (src[count] != NULL)
		count++;
	return (count);
}

char	**allocate_dest_array(int count)
{
	char	**dest;

	dest = malloc((count + 1) * sizeof(char *));
	if (!dest)
		exit(EXIT_FAILURE);
	return (dest);
}
