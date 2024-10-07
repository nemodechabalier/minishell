/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:05:03 by nde-chab          #+#    #+#             */
/*   Updated: 2024/10/07 17:33:05 by nde-chab         ###   ########.fr       */
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

void	wait_child(t_exec *exec)
{
	while (exec)
	{
		if (exec->cmd)
			wait(NULL);
		exec = exec->next;
	}
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

int	exec_and_red(t_data *data, t_exec *exec)
{
	t_redirection	*temp;

	creat_pipe(exec);
	while (exec)
	{
		temp = exec->red;
		while (temp)
		{
			dup_2_std(data);
			if (exec->red && redirection(temp, 0) == FAIL)
			{
				exec = exec->next;
				break ;
			}
			temp = temp->next;
		}
		if (!temp && is_builting(exec->cmd) && !exec->next && !exec->prev)
			ft_exec_red_built((exec), data);
		else if (!temp && exec->cmd)
			before_exec(exec, data);
		if (exec)
			exec = exec->next;
	}
	dup_2_std(data);
	return (SUCCESS);
}
