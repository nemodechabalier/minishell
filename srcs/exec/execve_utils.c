/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:58:11 by nde-chab          #+#    #+#             */
/*   Updated: 2024/10/15 15:05:09 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
	{
		return (-1);
	}
	return (S_ISDIR(path_stat.st_mode));
}

void	dup_2_std(t_data *data)
{
	dup2(data->stdin, STDIN_FILENO);
	dup2(data->stdout, STDOUT_FILENO);
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
		{
			is_here(0);
			temp->cmd->pid = waitpid(temp->cmd->pid, &status, 0);
		}
		temp = temp->next;
	}
	if (WIFEXITED(status) && data->exit_status == 0)
		data->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status) && data->exit_status == 0)
		data->exit_status = 128 + WTERMSIG(status);
	if (data->exit_status == 131)
		ft_putstr_fd("Quit (core dumped)\n", 2);
	if (data->exit_status == 130 && g_verif == 150)
		ft_putstr_fd("\n", 2);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sig);
}
