/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmanouk <clmanouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:39:56 by nde-chab          #+#    #+#             */
/*   Updated: 2024/09/24 17:03:11 by clmanouk         ###   ########.fr       */
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

t_redirection	*init_redirection(void)
{
	t_redirection	*red;

	red = (t_redirection *)malloc(sizeof(t_redirection));
	if (!red)
		return (NULL);
	red->pipes[0] = -1;
	red->pipes[1] = -1;
	red->file_fd = -1;
	red->file = NULL;
	red->stop = NULL;
	return (red);
}

t_cmd	*init_cmd(char **env)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->path_cmd = NULL;
	cmd->cmd = NULL;
	cmd->cmds = NULL;
	cmd->env = env;
	cmd->paths = NULL;
	cmd->skip = 0;
	if (env)
	{
		if (init_path(&cmd->paths, env) == FAIL)
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

t_data	*init_data(void)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->exec = NULL;
	data->parsing = NULL;
	return (data);
}
