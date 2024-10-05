/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:44:52 by nde-chab          #+#    #+#             */
/*   Updated: 2024/10/05 15:05:14 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_pipe(t_exec *exec)
{
	while (exec->prev)
		exec = exec->prev;
	while (exec->next)
	{
		if (close(exec->pipe[0]) == -1)
			perror("close1 :");
		if (close(exec->pipe[1]) == -1)
			perror("close2 :");
		exec = exec->next;
	}
}

int	ft_exec(t_cmd *cmd, t_data *data)
{
	close(data->stdin);
	close(data->stdout);
	data->stdin = -1;
	data->stdout = -1;
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

int	dup_pipe(t_exec *exec)
{
	if (exec->prev)
	{
		if (dup2(exec->prev->pipe[0], STDIN_FILENO) == -1)
			return (perror("pipe1"), close_pipe(exec), FAIL);
	}
	if (exec->next)
	{
		if (dup2(exec->pipe[1], STDOUT_FILENO) == -1)
			return (perror("pipe"), close_pipe(exec), FAIL);
	}
	close_pipe(exec);
	return (SUCCESS);
}

int	before_exec(t_exec *exec, t_data *data)
{
	t_redirection *temp;

	exec->cmd->pid = fork();
	if (exec->cmd->pid == -1)
		return (FAIL);
	else if (exec->cmd->pid == 0)
	{
		dup_pipe(exec);
		temp = exec->red;
		while (temp)
		{
			redirection(temp, 1);
			temp = temp->next;
		}
		if (exec->cmd)
		{
			ft_exec(exec->cmd, data);
		}
	}
	return (SUCCESS);
}