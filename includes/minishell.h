/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:17:37 by nde-chab          #+#    #+#             */
/*   Updated: 2024/10/07 17:28:30 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft_all/ft_printf/ft_printf.h"
# include "../libft_all/get_next_line/get_next_line.h"
# include "../libft_all/libtf/libft.h"
# include "parsing.h"
# include "exec.h"
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
# define ERROR_MALLOC 12

typedef struct s_pipe			t_pipe;
typedef struct s_list			t_list;
typedef struct s_env			t_env;

typedef struct s_remove
{
	char						**dest;
	char						*temp;
	int							i;
	int							j;
	int							size;
	int							count;
}								t_remove;

typedef struct s_env
{
	char						*value;
	char						*name;
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
void							ft_free_redirection(t_redirection **red);
void							ft_free_cmd(t_cmd **cmd);

// struct func
void							token_add_back(t_list **lst, t_list *new);
t_list							*create_new_token(char *token, int bool);
t_exec							*new_exec(void);
void							exec_add_back(t_exec **exec, t_exec *new);
void							ft_free_exec(t_exec **exec);
void							red_add_back(t_redirection **red,
									t_redirection *new);

t_data							*init_data(char **env);
t_cmd							*init_cmd(t_data *data);
t_env							*init_env(char *env);
int								env_size(t_env *env);

void							env_add_back(t_env **env, t_env *new);
int								creat_env(char **env, t_data *data);

void							ft_free_data(t_data **data);
void							ft_free_parsing(t_parsing **parsing);
void							ft_free_cmd(t_cmd **cmd);
void							ft_free_list(t_list **list);
void							ft_free_pipe(t_pipe **pipe);
void							free_after_exec(t_data *data);

// debug func
void							print_strs(char **strs);
void							print_token(t_parsing *parsing);

// utils
char							**get_env(t_data *data);
char							**ft_realloc(char **strs, int *size);

#endif