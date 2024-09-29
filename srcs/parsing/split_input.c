/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmanouk <clmanouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:05:27 by clmanouk          #+#    #+#             */
/*   Updated: 2024/09/29 17:34:26 by clmanouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_path(char **paths, t_cmd *cmd)
{
	char	*temp;

	int(i) = 0;
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
	cmd->path_cmd = NULL;
	cmd->skip = 2;
	return (SUCCESS);
}
int	add_flag_cmds(t_list *token, t_exec *exec)
{
	char	**split;
	char	**temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	split = ft_split(token->token, ' ');
	if (!split)
		return (FAIL);
	while (split[i])
		i++;
	while (exec->cmd->cmds[i])
		i++;
	temp = malloc(sizeof(char *) * (i + 1));
	if (!temp)
		return (ft_free_strs(split), FAIL);
	i = 0;
	j = 0;
	while (exec->cmd->cmds[i])
	{
		temp[i] = exec->cmd->cmds[i];
		i++;
	}
	while (split[j])
		temp[i++] = split[j++];
	temp[i] = NULL;
	exec->cmd->cmds = temp;
	return (SUCCESS);
}

int	split_input(t_list *token, t_exec *exec, char **env)
{
	char	**split;
	t_cmd	*cmd;

	if (exec->cmd)
		return (add_flag_cmds(token, exec));
	cmd = init_cmd(env);
	if (!cmd)
		return (FAIL);
	split = ft_split(token->token, ' ');
	if (!split)
		return (ft_free_cmd(&cmd), FAIL);
	cmd->cmds = split;
	cmd->cmd = split[0];
	find_path(cmd->paths, cmd);
	exec->cmd = cmd;
	return (SUCCESS);
}

