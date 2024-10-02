/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmanouk <clmanouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:44:52 by nde-chab          #+#    #+#             */
/*   Updated: 2024/10/01 18:15:17 by clmanouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_pipe(t_exec *exec)
{
	while (exec->prev)
		exec = exec->prev;
	while (exec->next)
	{
		close(exec->pipe[0]);
		close(exec->pipe[1]);
		exec = exec->next;
	}
}

int	ft_exec(t_cmd *cmd, t_data *data)
{
	//printf("%s\n", cmd->path_cmd);
	//print_strs(cmd->cmds);
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
		dup2(exec->prev->pipe[0], STDIN_FILENO);
	if (exec->next)
		dup2(exec->pipe[1], STDOUT_FILENO);
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
			ft_exec(exec->cmd, data);
	}
	return (SUCCESS);
}