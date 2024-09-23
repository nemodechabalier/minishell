/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmanouk <clmanouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:05:27 by clmanouk          #+#    #+#             */
/*   Updated: 2024/09/23 17:06:13 by clmanouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**split_input(t_parsing *parsing, t_data *cmd)
{
	char	**split;

	split = ft_split(parsing->input, ' ');
	cmd->exec->cmd->cmds = split;
	cmd->exec->cmd->cmd = split[0];
	return (split);
}

char	**split_input_d_quote(t_parsing *parsing)
{
	int		i;
	char	**split;
	char	*copy;
	int		start;

	i = 0;
	while (parsing->input[i])
	{
		if (parsing->input[i] == '"')
		{
			i++;
			start = i;
			while (parsing->input[i] && parsing->input[i] != '"')
				i++;
			if (parsing->input[i] == '"')
			{
				copy = ft_substr(parsing->input, start, i - start);
				split = ft_split(copy, ' ');
			}
			free(copy);
		}
		i++;
	}
	return (split);
}

char	**split_input_simple_quote(t_parsing *parsing)
{
	int i;
	char **split;
	char *copy;
	int start;

	i = 0;
	while (parsing->input[i])
	{
		if (parsing->input[i] == 27)
		{
			i++;
			start = i;
			while (parsing->input[i] && parsing->input[i] != 27)
				i++;
			if (parsing->input[i] == 27)
			{
				copy = ft_substr(parsing->input, start, i - start);
				split = ft_split(copy, ' ');
			}
			free(copy);
		}
		i++;
	}
	return (split);
}
