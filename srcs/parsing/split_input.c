/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:05:27 by clmanouk          #+#    #+#             */
/*   Updated: 2024/09/23 18:30:49 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_path(char **paths, t_cmd *cmd)
{
	int		i;
	char	*temp;

	i = 0;
	if (!cmd)
		return (FAIL);
	if (access(cmd->cmd, F_OK) == 0)
		return (cmd->path_cmd = cmd->cmd, SUCCESS);
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
			return (FAIL);
		cmd->path_cmd = ft_strjoin(temp, cmd->cmd);
		free(temp);
		if (!cmd->path_cmd)
			return (FAIL);
		if (access(cmd->path_cmd, F_OK) == 0)
			return (SUCCESS);
		else
			free(cmd->path_cmd);
		i++;
	}
	return (SUCCESS);
}

int	split_input(t_list *token, t_data *data, char **env)
{
	char	**split;
	t_exec	*new;
	t_cmd	*cmd;

	new = new_exec();
	if (!new)
		return (FAIL);
	cmd = init_cmd(env);
	if (!cmd)
		return (free(new), FAIL);
	split = ft_split(token->token, ' ');
	if (!split)
		return (ft_free_cmd(&cmd), free(new), FAIL);
	cmd->cmds = split;
	cmd->cmd = split[0];
	new->cmd = cmd;
	find_path(cmd->paths, cmd);
	exec_add_back(&data->exec, new);
	return (SUCCESS);
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
	int		i;
	char	**split;
	char	*copy;
	int		start;

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
