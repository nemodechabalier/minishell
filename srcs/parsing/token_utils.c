/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmanouk <clmanouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:30:39 by clmanouk          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2024/09/25 11:27:32 by clmanouk         ###   ########.fr       */
=======
/*   Updated: 2024/09/25 12:36:34 by nde-chab         ###   ########.fr       */
>>>>>>> Stashed changes
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
		parsing->input = readline("Minishell beta 1.1$ ");
		if (!parsing->input)
			break ;
		if (*parsing->input)
		{
			add_history(parsing->input);
			pars_token(parsing);
			print_token(parsing);
			creat_lst_red(data, data->parsing->tokens, env);
			//exec_and_red(data, data->exec);
			wait_child(data->exec);
			//free_after_exec(data);
		}
<<<<<<< Updated upstream
		pars_token(parsing);
		creat_lst_red(data, data->parsing->tokens, env);
		exec_and_red(data, data->exec);
		// ft_free_list(&parsing->tokens);
		free(parsing->input);
		parsing->input = NULL;
=======
>>>>>>> Stashed changes
	}
	return (0);
}

int	handle_quote(t_parsing *parsing, int start, int end)
{
	int		count;
	char	c;

	int(i) = start;
	count = -1;
	while (parsing->input[i] && i < end)
	{
		if (parsing->input[i] == 39 || parsing->input[i] == '"')
		{
			c = parsing->input[i];
			count = -count;
			i++;
			while (parsing->input[i] && i < end)
			{
				if (parsing->input[i] == c)
				{
					count = -count;
					break ;
				}
				i++;
			}
		}
		if (parsing->input[i])
			i++;
	}
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