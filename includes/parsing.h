/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:16:06 by nde-chab          #+#    #+#             */
/*   Updated: 2024/10/07 17:31:40 by nde-chab         ###   ########.fr       */
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

t_parsing						*init_parsing(void);
int								logical_operator(char c);
int								files_operator(char c);
int								handle_quote(char *input, int start, int end);
int								pars_token(t_parsing *parsing);

#endif