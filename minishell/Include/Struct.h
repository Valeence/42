/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zachamou <zachamou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 02:55:58 by zachamou          #+#    #+#             */
/*   Updated: 2024/06/27 23:27:15 by zachamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "../Include/MiniShell.h"

typedef enum e_type_token
{
	E_WORD = 10,
	E_IN = 11,
	E_OUT = 12,
	E_APPEND = 13,
	E_HEREDOC = 14,
	E_PIPE = 15,
	E_FILE = 16,
	E_EMPTY = 17,
	E_OEF_HERE = 20,
	E_NOT_CMD = 21,
	E_NEG = 22,
}					t_type_token;

typedef struct s_env
{
	char			**env;
}					t_env;

typedef struct s_here
{
	char			**delim;
	int				exe;
}					t_here;

typedef struct s_Token
{
	char			*token_str;
	char			**file;
	t_type_token	type;
	struct s_Token	*next;
}					t_Token;

typedef struct s_data2
{
	int				nb_file_out;
	int				nb_file_in;
	int				in_single_quote;
	int				in_double_quote;
	int				redi_and_here;
	int				pipe_bf_redi;
	int				*output_fd;
	int				*in_fd;
}					t_data2;

typedef struct s_data
{
	t_here			*here;
	t_Token			*curr_here_tmp;
	t_Token			*list_token_tmp;
	int				nb_cmd;
	char			*pronpt;
	char			**envp;
	char			**cmd;
	char			*path_exe;
	int				pipe_fd[2];
	int				here_fd[2];
	int				first;
	int				last;
	int				*in_fd_tmp;
	int				input_fd;
	int				redi_out_bf_pipe;
	int				flag_here;
	int				index;
	char			*str;
	char			*str_here;
	int				statusp;
	int				str_in;
	int				flag_qote;
	char			*home;
	t_data2			*data2;
	char			*valchar;
}					t_data;

#endif