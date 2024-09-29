/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:30:39 by clmanouk          #+#    #+#             */
/*   Updated: 2024/09/29 18:37:23 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

int	logical_operator(char c)
{
	if (c == '|')
		return (1);
	else if (c == '>')
		return (1);
	else if (c == '<')
		return (1);
	else
		return (0);
}

int	files_operator(char c)
{
	if (c == '>')
		return (1);
	else if (c == '<')
		return (1);
	return (0);
}

int	handle_input(t_parsing *parsing, t_data *data, char **env)
{
	set_signal_action();
	while (1)
	{
		parsing->input = readline("Minishell beta 2.0$ ");
		if (!parsing->input)
			break ;
		if (*parsing->input)
		{
			add_history(parsing->input);
			files_error(parsing);
			//pars_token(parsing);
			//print_token(parsing);
			creat_lst_red(data, data->parsing->tokens, env);
			pipe_error(parsing);
			exec_and_red(data, data->exec);
			wait_child(data->exec);
			free_after_exec(data);
		}
		parsing->input = NULL;
	}
	return (0);
}

int	handle_quote(char *input, int start, int end)
{
	int		count;
	char	c;

	int(i) = start;
	count = -1;
	while (input[i] && i < end)
	count = -1; //quand il y a le bon nb de quote
	while (input[i] && i < end)
	{
		if (input[i] == 39 || input[i] == '"')
		{
			c = input[i];
			count = -count;
			i++;
			while (input[i] && i < end)
			{
				if (input[i] == c)
				{
					count = -count;
					break ;
				}
				i++;
			}
		}
		if (input[i])
			i++;
	}
	printf("%d\n", count);
	return (count);
}

int	find_spaces(t_parsing *parsing)
{
	int i;

	i = 0;
	while (parsing->input[i])
	{
		if ((parsing->input[i] >= 9 && parsing->input[i] <= 13)
			|| parsing->input[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}