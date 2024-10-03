/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:39:56 by nde-chab          #+#    #+#             */
/*   Updated: 2024/10/03 14:55:22 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	init_path(char ***paths, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			*paths = ft_split(env[i] + 5, ':');
			if (!paths)
				return (FAIL);
			return (SUCCESS);
		}
		i++;
	}
	return (FAIL);
}

t_cmd	*init_cmd(t_data *data)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->path_cmd = NULL;
	cmd->cmd = NULL;
	cmd->cmds = NULL;
	cmd->env = NULL;
	if (get_env(data, cmd->env) == FAIL)
		return (ft_free_cmd(&cmd), NULL);
	print_strs(cmd->env);
	cmd->paths = NULL;
	cmd->skip = 0;
	if (cmd->cmd)
	{
		if (init_path(&cmd->paths, cmd->env) == FAIL)
			return (ft_free_cmd(&cmd), NULL);
	}
	return (cmd);
}

t_parsing	*init_parsing(void)
{
	t_parsing	*parsing;

	parsing = (t_parsing *)malloc(sizeof(t_parsing));
	if (!parsing)
		return (NULL);
	parsing->input = NULL;
	parsing->tokens = NULL;
	return (parsing);
}

t_data	*init_data(char **env)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->env = NULL;
	data->exec = NULL;
	data->parsing = NULL;
	if (creat_env(env, data) == FAIL)
		return (ft_free_data(&data), NULL);
	return (data);
}
