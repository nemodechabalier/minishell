/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:17:39 by nde-chab          #+#    #+#             */
/*   Updated: 2024/10/09 17:22:58 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "parsing.h"
# include <errno.h>
# include <sys/stat.h>
# include <sys/types.h>

typedef struct s_redirection	t_redirection;
typedef struct s_exec			t_exec;
typedef struct s_list			t_list;
typedef struct s_data			t_data;
typedef struct s_env			t_env;
typedef struct s_parsing		t_parsing;

typedef enum a_type
{
	HERE_DOC,
	TRUNC,
	APEND,
	INPUT,
}								t_type;

typedef struct s_redirection
{
	int							file_fd;
	char						*stop;
	char						*file;
	t_type						type;
	t_redirection				*next;
	t_redirection				*prev;
}								t_redirection;

typedef struct s_cmd
{
	int							skip;
	pid_t						pid;
	int							bool;
	char						**env;
	char						**paths;
	char						**cmds;
	char						*cmd;
	char						*path_cmd;
}								t_cmd;

typedef struct s_exec
{
	int							skip;
	int							pipe[2];
	t_redirection				*red;
	t_cmd						*cmd;
	t_exec						*next;
	t_exec						*prev;
}								t_exec;

// utils
int								is_directory(const char *path);

void							ft_exec(t_cmd *cmd, t_data *data);
t_redirection					*init_redirection(void);
void							close_fd(t_redirection *red);
int								before_exec(t_exec *exec, t_data *data);
int								here_doc(t_redirection *red);
int								split_input(t_list *token, t_exec *exec,
									t_data *data);
int								ft_exec_red_built(t_exec *exec, t_data *data);
int								creat_lst_red(t_data *data, t_list *lst);
int								exec_and_red(t_data *data, t_exec *exec);
void							wait_child(t_exec *exec, t_data *data);
void							close_exec(t_exec *exec);
int								redirection(t_redirection *red, int bool);
void							set_signal_action(void);
void							handle_sig(int signum);
int								join_cmd(t_data *data, t_list *list,
									char **env);
int								files_error(t_parsing *parsing);
int								pipe_error(t_parsing *parsing);
void							close_pipe(t_exec *exec);
int								find_var_env(t_parsing *parsing);
void							dup_2_std(t_data *data);

// builting
int								is_builting(t_cmd *cmd);
int								ft_exec_builting(t_cmd *cmd, t_data *data);
void							ft_cd(t_cmd *cmd, t_data *data);
void							ft_echo(t_cmd *cmd);
void							ft_env(t_data *data);
void							ft_export(t_data *data, t_cmd *cmd);
void							ft_pwd(t_data *data);
void							ft_exit(t_cmd *cmd);
int								ft_unset(t_cmd *cmd, t_data *data);
#endif