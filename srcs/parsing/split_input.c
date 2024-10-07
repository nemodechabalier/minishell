/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmanouk <clmanouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:05:27 by clmanouk          #+#    #+#             */
/*   Updated: 2024/10/07 18:09:51 by clmanouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_path(char **paths, t_cmd *cmd)
{
	char	*temp;

	int (i) = 0;
	if (ft_strchr(cmd->cmd, '/'))
		return (cmd->path_cmd = cmd->cmd, SUCCESS);
	if (!paths || cmd->cmd[0] == '\0')
		return (cmd->path_cmd = NULL, cmd->skip = 2, SUCCESS);
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

	int (i) = 0;
	int (j) = 0;
	split = remove_quote_cmd(token->token);
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
	while (exec->cmd->cmds[i++])
		temp[i] = exec->cmd->cmds[i];
	while (split[j])
		temp[i++] = split[j++];
	return (temp[i] = NULL, exec->cmd->cmds = temp, SUCCESS);
}

int	split_input(t_list *token, t_exec *exec, t_data *data)
{
	char	**split;
	t_cmd	*cmd;

	if (exec->cmd)
		return (add_flag_cmds(token, exec));
	cmd = init_cmd(data);
	if (!cmd)
		return (FAIL);
	split = remove_quote_cmd(token->token);
	if (!split)
		return (ft_free_cmd(&cmd), FAIL);
	cmd->cmds = split;
	cmd->cmd = split[0];
	find_path(cmd->paths, cmd);
	exec->cmd = cmd;
	return (SUCCESS);
}
