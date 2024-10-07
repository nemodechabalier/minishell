/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmanouk <clmanouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:30:39 by clmanouk          #+#    #+#             */
/*   Updated: 2024/10/07 18:40:35 by clmanouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	handle_input(t_parsing *parsing, t_data *data)
{
	set_signal_action();
	while (1)
	{
		parsing->input = readline("Minishell alpha 1.0$ ");
		if (!parsing->input)
			break ;
		if (*parsing->input)
		{
			add_history(parsing->input);
			printf("1 : reste des var 0 : non \n%d\n",
				interpret_var(parsing->input));
			// if (files_error(parsing) == SUCCESS && creat_lst_red(data,
			//		data->parsing->tokens) == SUCCESS
			//	&& pipe_error(parsing) == SUCCESS && exec_and_red(data,
			//		data->exec) == SUCCESS)
			//{
			//	close_pipe(data->exec);
			//	wait_child(data->exec);
			//}
		}
		free_after_exec(data);
	}
	return (0);
}

int	handle_quote(char *input, int start, int end)
{
	char	c;

	int(i) = start;
	int(count) = -1;
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
	return (count);
}

int	find_var_env(t_parsing *parsing)
{
	int	i;

	i = 0;
	while (parsing->input[i])
	{
		if (parsing->input[i] == '$')
			return (1);
		i++;
	}
	return (0);
}
