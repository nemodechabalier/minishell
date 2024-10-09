/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:16:06 by nde-chab          #+#    #+#             */
/*   Updated: 2024/10/09 16:07:00 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "./minishell.h"
# include "exec.h"
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_redirection	t_redirection;
typedef struct s_exec			t_exec;
typedef struct s_list			t_list;
typedef struct s_data			t_data;
typedef struct s_pipe			t_pipe;
typedef struct s_parsing		t_parsing;
typedef struct s_env			t_env;
typedef struct s_cmd			t_cmd;

extern int						g_verif;

typedef enum a_choice
{
	FILES,
	PIPES,
	CMD,
}								t_choice;

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

// paring
t_parsing						*init_parsing(void);
int								logical_operator(char c);
int								files_operator(char c);
int								handle_quote(char *input, int start, int end);
int								pars_token(t_parsing *parsing);

char							*remove_quote(char *str);
char							**remove_quote_cmd(char *str);
int								special_char_input(t_parsing *parsing);
int								handle_input(t_parsing *parsing, t_data *data);

// env var
int								which_quote(char *input, int end);
char							*take_name_2(char *input, int position);
int								interpret_var(char *input);
int								is_here_doc(char *input, int position);
char							*take_rest(char *input, int position);
char							*take_value(t_env *env, char *name,
									t_data *data);
int								var_env(t_parsing *parsing, t_env *env,
									t_data *data);

// signaux
void							signal_blocking(t_cmd *cmd);

#endif