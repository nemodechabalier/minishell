/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:17:37 by nde-chab          #+#    #+#             */
/*   Updated: 2024/09/23 17:13:09 by nde-chab         ###   ########.fr       */
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

typedef enum a_type
{
	PIPE,
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
	int							pipes[2];
	int							file_fd;
	char						*stop;
	char						*file;
	t_type						type;
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
	t_redirection				*next;
	t_redirection				*prev;
}								t_cmd;

typedef struct s_exec
{
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

typedef struct s_data
{
	t_parsing					*parsing;
	t_exec						*exec;
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
int								handle_input(t_parsing *parsing);

int								create_for_file(t_data *data, char *str,
									int bool);

// struct func
void							token_add_back(t_list **lst, t_list *new);
t_list							*create_new_token(char *token, int bool);
t_exec							*new_exec(void);
void							exec_add_back(t_exec **exec, t_exec *new);

t_data							*init_data(void);
t_parsing						*init_parsing(void);

void							ft_free_data(t_data **data);
void							ft_free_parsing(t_parsing **parsing);
void							ft_free_cmd(t_cmd **cmd);
void							ft_free_list(t_list **list);
void							ft_free_pipe(t_pipe **pipe);

// debug func
void							print_strs(char **strs);
void							print_token(t_parsing *parsing);

// exec func
int								ft_exec(t_cmd *cmd, t_data *data);
t_redirection					*init_redirection(void);
void							close_fd(t_redirection *red);
int								before_exec(t_cmd *cmd, t_data *data);
int								here_doc(t_redirection *red);

#endif