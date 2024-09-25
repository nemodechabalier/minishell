/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:05:03 by nde-chab          #+#    #+#             */
/*   Updated: 2024/09/25 10:53:32 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redirection_ok(t_exec *exec)
{
	if (!exec->next || !exec->next->cmd)
	{
		if (!exec->prev || !exec->prev->cmd)
			return(1);
	}
	return (0);
}

void	wait_child(t_exec *exec)
{
	while (exec)
	{
		if (exec->cmd)
			wait(NULL);
		exec = exec->next;
	}
}

void	close_exec(t_exec *exec)
{
	while (exec->prev)
		exec = exec->prev;
	while (exec)
	{
		if (exec->red)
			close_fd(exec->red);
		exec = exec->next;
	}
}

void	close_fd(t_redirection *red)
{
	if (red->file_fd != -1)
	{
		close(red->file_fd);
		red->file_fd = -1;
	}
	if (red->pipes[0] != -1)
	{
		close(red->pipes[0]);
		red->pipes[0] = -1;
	}
	if (red->pipes[1] != -1)
	{
		close(red->pipes[1]);
		red->pipes[1] = -1;
	}
}

int	redirection(t_redirection *red, int output, int bool)
{
	if (red->type == PIPE && bool)
	{
		if (output == 1)
			return (dup2(red->pipes[1], STDOUT_FILENO));
		return (dup2(red->pipes[0], STDIN_FILENO));
	}
	else if (red->type == HERE_DOC)
		here_doc(red, bool);
	else if (red->type == TRUNC)
	{
		red->file_fd = open(red->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (red->file_fd == -1)
			return (perror(red->file), FAIL);
		if (bool)
			dup2(red->file_fd, STDOUT_FILENO);
	}
	else if (red->type == TRUNC)
	{
		red->file_fd = open(red->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (red->file_fd == -1)
			return (perror(red->file), FAIL);
		if (bool)
			dup2(red->file_fd, STDOUT_FILENO);
	}
	else if (red->type == INPUT)
	{
		red->file_fd = open(red->file, O_RDONLY);
		if (red->file_fd == -1)
			return (perror(red->file), FAIL);
		if (bool)
			dup2(red->file_fd, STDIN_FILENO);
	}
	return (SUCCESS);
}

int	exec_and_red(t_data *data, t_exec *exec)
{
	while (exec)
	{
		if (exec->red && redirection_ok(exec))
			redirection(exec->red, 1, 0);
		if (exec->cmd)
			before_exec(exec, data);
		exec = exec->next;
	}
	return (SUCCESS);
}
