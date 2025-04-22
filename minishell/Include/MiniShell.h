/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MiniShell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zachamou <zachamou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 02:55:02 by zachamou          #+#    #+#             */
/*   Updated: 2024/06/27 23:31:59 by zachamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PIP "|"
# define RDI_IN "<"
# define RDI_OUT ">"
# define S_QOTES '\''
# define D_QOTES '\"'

# include "./libft/libft.h"
# include "Struct.h"
# include <ctype.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

extern int	g_gvalret;
void		print_list(t_Token *begin);
void		ft_lexer(t_data *data, t_Token **list_token);
int			extract_token(const char *readline, int start, char **token,
				t_data *data);
int			skip_begin_spaces_prompt(const char *readline, int start);
bool		ft_is_del(char c);
bool		ft_isspace(char c);
t_Token		*creat_noed_token(char *token);
void		add_token(t_Token **begin, t_Token *new_token);
void		ft_supp_noed_empy(t_Token **list_tok);
void		free_token(t_Token *begin);
int			ft_size_list_token(t_Token *list_token);
void		free_lst(t_Token *lst);
void		insert_nodes_at_current(t_Token *current, int size);
bool		shr_out_in_redi(t_Token *curr);
bool		search_redi(t_Token *curr);
void		push_position(t_Token **curr, int grab_hd);
void		ft_analy_type_pipe(t_Token **current);
void		ft_analy_type_redi_out(t_Token **current, t_data *data);
void		ft_analy_type_redi_append(t_Token **current, t_data *data);
void		ft_analy_type_redi_heredoc(t_Token **current);
void		ft_analy_type_else(t_data *data, t_Token **current);
void		ft_analy_type_redi_in(t_data *data, t_Token **current);
void		ft_lanch_exe(t_data *data, t_Token *list_token);
void		ft_simple_cmd(t_data *data, t_Token *list_token);
char		*ft_get_reading(t_data *data, t_Token *list_token);
void		ft_no_patch(t_data *data);
int			open_output_fd(t_data *data, t_Token *tmp);
int			open_append_fd(t_data *data, t_Token *tmp);
void		handle_open_error(int fd, char *filename);
bool		shr_out_in_here(t_Token *lst);
void		init_data(t_data *data);
void		ft_free_tabtab(char **split_result);
int			ft_verify_pipe_separation(t_Token *list_token);
void		execute_pipeline_redirection(t_data *data, t_Token *list_token);
pid_t		fork_process_redi_out(t_data *data, t_Token *curr);
pid_t		fork_process_redi_in(t_data *data, t_Token *curr);
pid_t		fork_process_pipe(int i, t_data *data, t_Token *curr);
void		create_pipe(int pipe_fd[2], int i, int last);
void		close_pipes_in_parent(int i, t_data *data, int *input_fd);
void		wait_for_children(t_data *data, int last, pid_t pid[]);
char		*build_executable_path(char *cmd, char *path);
int			cont_nb_out(t_Token *curr);
char		*read_until_delimiter(t_here *here);
bool		shr_out_in_redi_in_for_stop(t_Token *curr);
bool		shr_out_in_redi_3(t_Token *curr);
void		ft_redi_out_bf_pipe(t_data *data);
void		push_to(t_Token *tmp, t_data *data);
bool		check_here(t_Token *curr);
bool		check_here_2(t_Token *curr);
bool		check_in(t_Token *curr);
bool		check_out(t_Token *curr);
bool		check_pipe(t_Token *curr);
void		close_or_not(t_data *data, pid_t pid);
void		push_exe(t_Token **curr, t_data *data);
void		push_in(t_Token **curr);
void		free_for_exe_exit(t_data *data, t_Token *curr);
char		**copy_array_arrays(char **src);
void		free_for_exe_exit(t_data *data, t_Token *curr);
void		close_fd_in(t_data *data);
int			*creat_fd_in(t_data *data, t_Token *curr);
int			*creat_fd_out(t_data *data, t_Token *curr);
void		close_fd_out(t_data *data);
int			cont_nb_in(t_Token *curr);
bool		verif_pipe(t_Token *curr);
void		lanch_her(t_Token *curr, t_data *data);
char		*ft_get_reading_in(t_data *data, t_Token *curr);
void		execute_double_in_1(t_data *data, t_Token **curr);
void		execute_double_in_2(t_data *data, t_Token **curr); // pas necessaire
void		execute_in(t_data *data, t_Token **curr, pid_t *pid);
void		execute_redi_out_and_append(t_data *data, t_Token **curr,
				pid_t *pid);
void		execute_pipe(t_data *data, t_Token **curr, pid_t *pid);
char		*ft_strcat(char *dest, char *src);
void		free_for_exe(t_data *data, t_Token *curr);
int			cont_nb_here(t_Token *curr);
int			fork_here(t_Token *curr, t_data *data, t_here *here);
int			*creat_fd_out_in_in(t_data *data, t_Token *curr);
int			concatenate_lines(t_data *data, char *line);
int			syntaxize_moi_ca(char *str);
int			check_builtins(t_data *data, t_Token *curr, char **envp);
void		free_tokens(char **tokens, char *str);
int			ft_isalnum_env(int c);
char		**create_new_env(int env_size);
int			*fill_tab(char *str, int i, int *tab);
void		free_tokens(char **tokens, char *str);
int			add_new_var(t_data *data, char *str);
int			update_existing_var(t_data *data, char *str, int name_len);
void		process_arg(char *arg, t_data *data);
int			parentheses_check(char *str);
char		**copy_array_arrays(char **src);
bool		in_file(t_Token *curr);
bool		in_file_2(t_Token *curr);
void		copy_string(char **dest, const char *src, int index);
int			count_strings(char **src);
char		**allocate_dest_array(int count);
void		bye_bye_in(t_data *data, t_Token *curr);
char		**ft_split_quoted(char const *s);
char		**allocate_result_array(char const *s);
int			process_word(const char *s, int i, char **result, int *k);
void		copy_word(const char *substring, int len, char **result, int *k);
int			ft_cd(t_Token *curr, t_data *data);
int			ft_pwd(t_data *data);
int			ft_echo(t_data *data, t_Token *cur);
int			ft_env(char **envp);
int			check_env(char *str);
void		ft_exit(t_data *date, t_Token *curr);
int			ft_export(t_data *data, t_Token *curr);
int			ft_unset(t_data *data, t_Token *curr);
char		*remove_quotes(char *str);
int			ft_isalnum_env(int c);
void		free_tokens(char **tokens, char *str);
int			add_new_var(t_data *data, char *str);
char		**ft_split_quoted_echo(char const *s);
int			*init_vars(void);
int			fonction_qote(char c, int flag_supp_qote, t_data *data);
void		signal_handle(int i);
void		aff_exit_code(t_data *data);

#endif
