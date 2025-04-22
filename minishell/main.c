/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zachamou <zachamou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 23:42:04 by zachamou          #+#    #+#             */
/*   Updated: 2024/06/27 23:42:14 by zachamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Include/MiniShell.h"

int		g_gvalret;

void	signal_handle(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	if (!g_gvalret)
		g_gvalret = 130;
	else
		g_gvalret = 0;
}

char	**copy_env(char **envp)
{
	int		i;
	char	**new_env;

	i = 0;
	while (envp[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env[i])
		{
			while (i > 0)
				free(new_env[--i]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

void	list_no_null(t_data *data, t_Token *list_token)
{
	ft_lanch_exe(data, list_token);
	add_history(data->pronpt);
	free(data->pronpt);
	free_token(list_token);
}

void	while_mini(t_data *data)
{
	t_Token	*list_token;

	list_token = NULL;
	while (1)
	{
		g_gvalret = 0;
		list_token = NULL;
		init_data(data);
		data->pronpt = readline("Minishell$ ");
		if (!data->pronpt)
			break ;
		if (!*data->pronpt)
			continue ;
		if (syntaxize_moi_ca(data->pronpt) == 1)
		{
			ft_lexer(data, &list_token);
			data->list_token_tmp = list_token;
			if (list_token != NULL)
				list_no_null(data, list_token);
		}
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	char	**envp_copy;

	(void)ac;
	(void)av;
	signal(SIGINT, signal_handle);
	signal(SIGQUIT, SIG_IGN);
	envp_copy = copy_env(env);
	data.envp = envp_copy;
	data.statusp = 0;
	data.home = ft_strdup(getenv("PWD"));
	data.data2 = malloc(sizeof(t_data2));
	if (!data.data2)
	{
		perror("Failed to allocate memory for data2");
		exit(EXIT_FAILURE);
	}
	while_mini(&data);
	free(data.data2);
	return (0);
}
