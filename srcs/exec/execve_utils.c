/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:58:11 by nde-chab          #+#    #+#             */
/*   Updated: 2024/10/08 17:35:53 by nde-chab         ###   ########.fr       */
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