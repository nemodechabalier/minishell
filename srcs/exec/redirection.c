/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:05:03 by nde-chab          #+#    #+#             */
/*   Updated: 2024/10/09 16:37:00 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	creat_pipe(t_exec *exec)
{
	while (exec->next)
	{
		if (pipe(exec->pipe) == -1)
			return (perror("pipe :"), FAIL);
		exec = exec->next;
	}
	return (SUCCESS);
}

void	wait_child(t_exec *exec, t_data *data)
{
	t_exec	*temp;
	int		status;

	temp = exec;
	status = 0;
	while (temp)
	{
		if (temp->cmd && temp->cmd->bool == 1)
			temp->cmd->pid = waitpid(temp->cmd->pid, &status, 0);
		temp = temp->next;
	}
	if (WIFEXITED(status) && data->exit_status == 0)
		data->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status) && data->exit_status == 0)
		data->exit_status = 128 + WTERMSIG(status);
	signal(SIGQUIT, SIG_IGN);
}

int	redirection_2(t_redirection *red, int bool)
{
	if (red->type == APEND)
	{
		red->file_fd = open(red->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (red->file_fd == -1)
			return (perror(red->file), FAIL);
		if (bool)
			dup2(red->file_fd, STDOUT_FILENO);
		close(red->file_fd);
	}
	else if (red->type == INPUT)
	{
		red->file_fd = open(red->file, O_RDONLY);
		if (red->file_fd == -1)
			return (perror(red->file), FAIL);
		if (bool)
			dup2(red->file_fd, STDIN_FILENO);
		close(red->file_fd);
	}
	return (SUCCESS);
}

int	redirection(t_redirection *red, int bool)
{
	if (red->type == HERE_DOC)
	{
		if (!bool)
			here_doc(red);
		red->file_fd = open(red->file, O_RDONLY);
		dup2(red->file_fd, STDIN_FILENO);
	}
	else if (red->type == TRUNC)
	{
		red->file_fd = open(red->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (red->file_fd == -1)
			return (perror(red->file), FAIL);
		if (bool)
			dup2(red->file_fd, STDOUT_FILENO);
		close(red->file_fd);
	}
	return (redirection_2(red, bool));
}
int	open_file(t_exec *exec, t_data *data)
{
	t_exec			*temp;
	t_redirection	*current;

	temp = exec;
	while (temp)
	{
		current = temp->red;
		while (current)
		{
			dup_2_std(data);
			if (g_verif == 5)
				return (dup_2_std(data), FAIL);
			if (temp->red && redirection(current, 0) == FAIL)
			{
				temp = temp->next;
				temp->skip = 1;
				if (!temp)
					data->exit_status = 1;
				break ;
			}
			current = current->next;
		}
		temp = temp->next;
	}
	g_verif = 0;
	return (SUCCESS);
}

int	exec_and_red(t_data *data, t_exec *exec)
{
	data->exit_status = 0;
	creat_pipe(exec);
	if (open_file(exec, data) == FAIL)
		return (g_verif = 0, FAIL);
	while (exec)
	{
		if (exec->cmd && exec->skip == 0 && is_builting(exec->cmd)
			&& !exec->next && !exec->prev)
			ft_exec_red_built((exec), data);
		else if (exec->cmd && exec->skip == 0)
			before_exec(exec, data);
		exec = exec->next;
	}
	dup_2_std(data);
	return (SUCCESS);
}
