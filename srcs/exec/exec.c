/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:44:52 by nde-chab          #+#    #+#             */
/*   Updated: 2024/09/24 16:57:24 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_exec(t_cmd *cmd, t_data *data)
{
	(void)data;
	if (cmd->skip == 2)
	{
		ft_putstr_fd(cmd->cmds[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		ft_free_data(&data);
		exit(EXIT_FAILURE);
	}
	else if (cmd->skip == 1)
	{
		ft_free_data(&data);
		exit(EXIT_FAILURE);
	}
	else if (execve(cmd->path_cmd, cmd->cmds, cmd->env) == -1)
	{
		perror(cmd->cmds[0]);
		ft_free_data(&data);
		exit(EXIT_FAILURE);
	}
	return (FAIL);
}

int	before_exec(t_exec *exec, t_data *data)
{
	exec->cmd->pid = fork();
	if (exec->cmd->pid == -1)
		return (FAIL);
	else if (exec->cmd->pid == 0)
	{
		if (exec->next && exec->next->red && redirection(exec->next->red, 1,
				1) == FAIL)
			exec->cmd->skip = 1;
		if (exec->prev && exec->prev->red && redirection(exec->prev->red, 0,
				1) == FAIL)
			exec->cmd->skip = 1;
		close_exec(data->exec);
		ft_exec(exec->cmd, data);
	}
	return (SUCCESS);
}