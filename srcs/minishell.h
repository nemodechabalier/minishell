#ifndef MINISHELL_H
#define MINISHELL_H

#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

typedef struct s_pipe t_pipe;

typedef struct s_pipe
{
	int tab[2];
	t_pipe *next;
	t_pipe *prev;
} t_pipe;

typedef struct s_cmd
{
	char **env;
	char **paths;
	char **cmds;
	char *cmd;
	t_pipe *pipe;
} t_cmd;

typedef struct s_parsing
{
	char *input;
	char **tokens;
} t_parsing;

typedef struct s_data
{
	t_parsing *parsing;
	t_cmd *cmd;
} t_data;

#define FALSE 0
#define TRUE 1
#define FAIL -1
#define SUCCESS 2

#endif