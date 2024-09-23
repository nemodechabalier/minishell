/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:05:03 by nde-chab          #+#    #+#             */
/*   Updated: 2024/09/23 13:22:20 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	redirection(t_redirection *red, int output)
{
	if (red->type == PIPE)
	{
		if (output = 1)
			return (dup2(red->pipes[1], STDOUT_FILENO));
		return (dup2(red->pipes[0], STDIN_FILENO));
	}
	else if (red->type == HERE_DOC)
		ft_here_doc();
	else if (red->type == INPUT)
	{
		red->file_fd = open(red->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (red->file_fd == -1)
			return (perror(red->file), FAIL);
		dup2(red->file_fd, STDOUT_FILENO);
	}
	else if (red->type == TRUNC)
	{
		red->file_fd = open(red->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (red->file_fd == -1)
			return (perror(red->file), FAIL);
		dup2(red->file_fd, STDOUT_FILENO);
	}
	else if (red->type == INPUT)
	{
		red->file_fd = open(red->file, O_RDONLY);
		if (red->file_fd == -1)
			return (perror(red->file), FAIL);
		dup2(red->file_fd, STDIN_FILENO);
	}
	return (SUCCESS);
}

int	exec_and_red(t_data *data, t_exec *exec)
{
	while (exec)
	{
		if (exec->red)
		{
			if (redirection(exec->red, 0) == FAIL && exec->next
				&& exec->next->cmd)
				exec->next->cmd->skip = 0;
			exec = exec->next;
		}
		if (exec->cmd)
		{
			if (exec->next && exec->next->red && redirection(exec->next->red,
					1) != FAIL)
				ft_exec(exec->cmd, data);
		}
		exec = exec->next;
	}
}
