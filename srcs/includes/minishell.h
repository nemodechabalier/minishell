/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmanouk <clmanouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:17:37 by nde-chab          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2024/09/28 13:25:49 by clmanouk         ###   ########.fr       */
=======
/*   Updated: 2024/09/26 15:33:04 by clmanouk         ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../../libft_all/ft_printf/ft_printf.h"
# include "../../libft_all/get_next_line/get_next_line.h"
# include "../../libft_all/libtf/libft.h"
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# define FALSE 0
# define TRUE 1
# define FAIL -1
# define SUCCESS 2
# define PATH_MAX 4096
# define ERROR_UNCLOSE 10
# define ERROR_D_PIPE 11

typedef struct s_pipe			t_pipe;
typedef struct s_list			t_list;
typedef struct s_exec			t_exec;
typedef struct s_redirection	t_redirection;
typedef struct s_cmd			t_cmd;
typedef struct s_env			t_env;

typedef enum a_type
{
	HERE_DOC,
	TRUNC,
	APEND,
	INPUT,
}								t_type;

typedef enum a_choice
{
	FILES,
	PIPES,
	CMD,
}								t_choice;

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
	char						**env;
	char						**paths;
	char						**cmds;
	char						*cmd;
	char						*path_cmd;
}								t_cmd;

typedef struct s_exec
{
	int							pipe[2];
	t_redirection				*red;
	t_cmd						*cmd;
	t_exec						*next;
	t_exec						*prev;
}								t_exec;

typedef struct s_parsing
{
	char						*input;
	t_list						*tokens;
}								t_parsing;

typedef struct s_list
{
	char						*token;
	t_choice					type;
	t_list						*next;
	t_list						*prev;
}								t_list;
typedef struct s_env
{
	char						*env;
	t_env						*next;
	t_env						*prev;
}								t_env;

typedef struct s_data
{
	t_parsing					*parsing;
	t_exec						*exec;
	t_env						*env;
	int							stdin;
	int							stdout;
}								t_data;

// free func
void							ft_free_strs(char **strs);
void							ft_free_data(t_data **data);

// token func
int								logical_operator(char c);
int								files_operator(char c);
int								handle_quote(t_parsing *parsing, int start,
									int end);
int								pars_token(t_parsing *parsing);

// struct func
void							token_add_back(t_list **lst, t_list *new);
t_list							*create_new_token(char *token, int bool);
t_exec							*new_exec(void);
void							exec_add_back(t_exec **exec, t_exec *new);
void							ft_free_exec(t_exec **exec);
void							red_add_back(t_redirection **red,
									t_redirection *new);

t_data							*init_data(void);
t_parsing						*init_parsing(void);
t_cmd							*init_cmd(char **env);
t_env							*init_env(char *env);
void							env_add_back(t_env **env, t_env *new);
int								creat_env(t_env *env, t_data *data);

void							ft_free_data(t_data **data);
void							ft_free_parsing(t_parsing **parsing);
void							ft_free_cmd(t_cmd **cmd);
void							ft_free_list(t_list **list);
void							ft_free_pipe(t_pipe **pipe);
void							free_after_exec(t_data *data);

// debug func
void							print_strs(char **strs);
void							print_token(t_parsing *parsing);

// exec func
int								ft_exec(t_cmd *cmd, t_data *data);
t_redirection					*init_redirection(void);
void							close_fd(t_redirection *red);
int								before_exec(t_exec *exec, t_data *data);
int								here_doc(t_redirection *red);
int								split_input(t_list *token, t_exec *exec,
									char **env);
int								handle_input(t_parsing *parsing, t_data *data,
									char **env);
int								creat_lst_red(t_data *data, t_list *lst,
									char **env);
int								exec_and_red(t_data *data, t_exec *exec);
void							wait_child(t_exec *exec);
void							close_exec(t_exec *exec);
int								redirection(t_redirection *red, int bool);

void							set_signal_action(void);
void							handle_sig(int signum);
int								join_cmd(t_data *data, t_list *list,
									char **env);
int								first_operator(t_parsing *parsing);

#endif