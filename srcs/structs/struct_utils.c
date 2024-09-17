/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:39:56 by nde-chab          #+#    #+#             */
/*   Updated: 2024/09/17 14:05:02 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	init_path(char **paths, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], "PATH=", 5))
		{
			paths = ft_split(env[i] + 5, ':');
			if (!paths)
				return (FAIL);
			return (paths);
		}
		i++;
	}
	return (FAIL);
}
t_cmd	*init_cmd(char **env)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd *));
	if (!cmd)
		return (NULL);
	cmd->path_cmd = NULL;
	cmd->cmds = NULL;
	cmd->env = env;
	cmd->paths = NULL;
	if (env)
		init_path(cmd->paths, env);
	return (cmd);
}

t_parsing	*init_parsing(void)
{
	t_parsing	*parsing;

	parsing = (t_parsing *)malloc(sizeof(t_parsing *));
	if (!parsing)
		return (NULL);
	parsing->input = NULL;
	parsing->tokens = NULL;
}

t_data	*init_data(void)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data *));
	if (!data)
		return (NULL);
	data->cmd = NULL;
	data->parsing = NULL;
	return (data);
}
